#ifndef ITEM_H
#define ITEM_H

#include <QString>

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
        item_name  goods;
        int        year;
        int        status;
        double     true_price;
        double     estimated_price;
        bool       is_fake;
    };

    double    rarity_rate[7]={1,2,5,15,50,200,1000};
    double    status_rate[7]={0.3,0.6,0.8,1,1.3,1.9,3};
    item_name name_list[200];

public:
    QString   rarity_list[7]={"平凡","普通","稀有","罕见","史诗","传说","神话"};
    QString   status_list[7]={"报废","极差","差","一般","翻新","良好","极佳"};
};

#endif // ITEM_H
