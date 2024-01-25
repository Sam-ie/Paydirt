#ifndef FUTURE_GOODS_H
#define FUTURE_GOODS_H

#include <QString>

struct Future_goods
    {
        //商品序号、商品名、商品等级、原价、现商品价格、商品总数量、玩家持有数量、他人持有数量、商品涨跌情况、历史涨跌情况、购买价格、上次购买时价格
        int     serial_num;
        QString goods;
        int     goods_level;
        int     origin_price;
        double  cur_price;
        int     total_num;
        int     player_num;
        int     others_num;
        double  last_fluctuation;
        double  total_fluctuation;
        double  buy_price;
        double  last_buy_price;
    };

//商品列表
static Future_goods fgs[25];

#endif // FUTURE_GOODS_H
