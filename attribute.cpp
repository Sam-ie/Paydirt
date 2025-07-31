#include "attribute.h"

Attribute::Attribute()
{
    // 尝试从JSON加载数据
    loadFromJson();
}

Attribute::~Attribute()
{
    // 析构时自动保存
    saveToJson();
}

QString Attribute::getAttributeText()
{
    return QString("口才：%1\t 能力：%2\n"
                   "洞察力：%3\t 店铺等级：%4\n"
                   "幸运：%5\t 声望：%6\n")
              .arg(QString::number(eloquence)).arg(QString::number(ability))
              .arg(QString::number(insight)).arg(shop_level_list[shop_level-1])
              .arg(QString::number(luck)).arg(reputation_list[reputation-1]);
}

void Attribute::loadFromJson() {
    QFile file(Player::getJsonFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();

    // 读取 attribute 子对象
    QJsonObject attrObj = json.contains("attribute") ? json["attribute"].toObject() : QJsonObject();

    // 从JSON读取值，如果不存在则使用默认值
    eloquence  = attrObj.contains("eloquence") ? attrObj["eloquence"].toInt() : 1;
    ability    = attrObj.contains("ability") ? attrObj["ability"].toDouble() : 1;
    insight    = attrObj.contains("insight") ? attrObj["insight"].toDouble() : 1;
    luck       = attrObj.contains("luck") ? attrObj["luck"].toInt() : 1;
    shop_level = attrObj.contains("shop_level") ? attrObj["shop_level"].toDouble() : 1;
    reputation = attrObj.contains("reputation") ? attrObj["reputation"].toDouble() : 7;
}

void Attribute::saveToJson() {
    QFile file(Player::getJsonFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();
    file.close();

    // 创建或更新 attribute 对象
    QJsonObject attrObj;
    attrObj["eloquence"]   = eloquence;
    attrObj["ability"]     = ability;
    attrObj["insight"]     = insight;
    attrObj["luck"]        = luck;
    attrObj["shop_level"]  = shop_level;
    attrObj["reputation"]  = reputation;

    json["attribute"] = attrObj;

    // 使用 QSaveFile 安全写回
    QSaveFile saveFile(Player::getJsonFilePath());
    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }

    saveFile.write(QJsonDocument(json).toJson());
    saveFile.commit();
}
