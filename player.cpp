#include "player.h"
#include "futures.h"

Player *Player::instance() {
    static Player instance;
    return &instance;
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
        QRandomGenerator* rand = QRandomGenerator::global();
        int random_rate = rand->bounded(800000)-100000*(difficulty+1);
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
    QFile file(Player::getJsonFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();
    file.close();

    QJsonObject playerObj;
    playerObj["difficulty"] = difficulty;
    playerObj["cur_money"] = cur_money;
    playerObj["future_money"] = future_money;
    playerObj["round"] = round;
    playerObj["whole_market_fluctuation"] = whole_market_fluctuation;

    json["player"] = playerObj;

    QSaveFile saveFile(getJsonFilePath());
    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }

    saveFile.write(doc.toJson());
    saveFile.commit();
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
        QSaveFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return;
        }

        QJsonObject jsonObj;
        QJsonDocument doc(jsonObj);
        file.write(doc.toJson());
        file.commit();
    }

    // 3. 正常读取现有文件
    QFile loadFile(filePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    // 获取player对象
    QJsonObject playerObj = json.contains("player") ? json["player"].toObject() : QJsonObject();

    // 从JSON读取值，如果不存在则使用默认值
    difficulty = playerObj.contains("difficulty") ? playerObj["difficulty"].toInt() : 0;
    cur_money = playerObj.contains("cur_money") ? playerObj["cur_money"].toDouble() : -1;
    future_money = playerObj.contains("future_money") ? playerObj["future_money"].toDouble() : 0;
    round = playerObj.contains("round") ? playerObj["round"].toInt() : 0;
    whole_market_fluctuation = playerObj.contains("whole_market_fluctuation") ? playerObj["whole_market_fluctuation"].toDouble() : 0;

    // 如果round为0，执行setRound()
    // if (round == 0) {// 错误写法
    //     setRound(); // setround调用的futures中再次调用了player实例。程序中存在构造函数在初始化期间间接再次调用自身 的情况，也就是所谓的 构造函数重入（reentrant construction），导致“看似单例却多次执行构造函数”的假象。
    // }
}
