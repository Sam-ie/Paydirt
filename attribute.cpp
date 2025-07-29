#include "attribute.h"

Attribute::Attribute() {}

QString Attribute::getAttributeText()
{
    return QString("口才：%1\t 能力：%2\n"
                   "洞察力：%3\t 幸运: %4\n"
                   "店铺等级：%5\t 声望：%6\n")
              .arg((QString::number(eloquence)).arg(QString::number(ability))
              .arg(QString::number(insight)).arg(QString::number(luck))
              .arg(shop_level_list[shop_level-1]).arg(reputation_list[reputation-1]));
}
