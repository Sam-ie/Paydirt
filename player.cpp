#include "player.h"
#include "futures.h"

Player *Player::instance() {
    static Player *instance = nullptr;
    if (!instance) {
        instance = new Player();
    }
    return instance;
}

Player::Player()
{
    // 尝试从JSON加载数据
    loadFromJson();
}

Player::~Player()
{
    // 析构时自动保存
    saveToJson();
}

int Player::getDifficulty() const
{
    return difficulty;
}

void Player::setDifficulty(int newdifficulty)
{
    this->difficulty = newdifficulty;
    if (cur_money==-1)
        cur_money=6000-1000*difficulty;
}

double Player::getCur_money() const
{
    return cur_money;
}

void Player::setCur_money(double newCur_money)
{
    cur_money += newCur_money;
}

double Player::getFuture_money() const
{
    return future_money;
}

void Player::setFuture_money(double newfuture_money)
{
    future_money += newfuture_money;
}

int Player::getRound() const
{
    return round;
}

void Player::setRound()
{
    round++;
    if (round%8==1)
    {
        QRandomGenerator generator;
        generator.seed(QDateTime::currentDateTime().toMSecsSinceEpoch());
        int random_rate = generator.bounded(800000)-100000*(difficulty+1);
        //对应-2%——6% -3%——5% -4%——4% (1.04*0.96<1)
        whole_market_fluctuation = (double)random_rate/100000;
    }
    if (round%40==17)
        whole_market_fluctuation-=9-3*difficulty;
    Futures::instance()->do_update();
}

double Player::getWhole_Market_Fluctuation() const
{
    return whole_market_fluctuation;
}

void Player::saveToJson()
{
    QJsonObject json;
    json["difficulty"] = difficulty;
    json["cur_money"] = cur_money;
    json["future_money"] = future_money;
    json["round"] = round;
    json["whole_market_fluctuation"] = whole_market_fluctuation;

    QFile saveFile(getJsonFilePath());
    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }

    QJsonDocument saveDoc(json);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
}

void Player::loadFromJson()
{
    QString filePath = getJsonFilePath();
    QFileInfo fileInfo(filePath);
    QDir dir(fileInfo.absolutePath());

    // 1. 确保目录存在
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // 2. 检查文件是否存在，不存在则创建并写入默认值
    if (!fileInfo.exists()) {
        QFile file(filePath);
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        // 初始化默认JSON数据
        QJsonObject defaultJson;
        defaultJson["difficulty"] = 0;
        defaultJson["cur_money"] = -1;
        defaultJson["future_money"] = 0;
        defaultJson["round"] = 0;
        defaultJson["whole_market_fluctuation"] = 0;

        QJsonDocument doc(defaultJson);
        file.write(doc.toJson());
        file.close();
    }

    // 3. 正常读取现有文件
    QFile loadFile(filePath);
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    // 从JSON读取值，如果不存在则使用默认值
    difficulty = json.contains("difficulty") ? json["difficulty"].toInt() : 0;
    cur_money = json.contains("cur_money") ? json["cur_money"].toDouble() : -1;
    future_money = json.contains("future_money") ? json["future_money"].toDouble() : 0;
    round = json.contains("round") ? json["round"].toInt() : 0;
    whole_market_fluctuation = json.contains("whole_market_fluctuation")
                                   ? json["whole_market_fluctuation"].toDouble() : 0;

    // 如果round为0，执行setRound()
    if (round == 0) {
        setRound();
    }
    return;
}
