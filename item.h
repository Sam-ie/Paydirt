#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QList>
#include <QRandomGenerator>

class Item
{
public:
    Item();


private:
    struct item_name
    {
        int     earliest_year;
        int     latest_year;
        int     rarity;
        QString item_type;
        QString description = "";
        double  base_price;
    };

    struct Antique_goods
    {
        int        id;
        item_name  item;
        int        year;
        int        status;
        double     true_price;
        double     estimated_price;
        bool       is_fake;
    };

    double    rarity_rate[7]={1,2,5,15,50,200,1000};
    double    status_rate[7]={0.3,0.6,0.8,1,1.3,1.9,3};
    item_name name_list[200];

    int    next_id;

    // 辅助函数：保留指定有效数字
    static double roundToSignificantDigits(double value, int digits) {
        if (value == 0.0) return 0.0;
        double factor = std::pow(10.0, digits - std::ceil(std::log10(std::fabs(value))));
        return std::round(value * factor) / factor;
    }

public:
    QString   rarity_list[7]={"平凡","普通","稀有","罕见","史诗","传说","神话"};
    QString   status_list[7]={"报废","极差","差","一般","翻新","良好","极佳"};
    int       reputation_to_year[7]={10,30,80,200,500,1250,6500};
    // 生成古董物品的函数
    Antique_goods generateAntique(int reputation);

};

#endif // ITEM_H
