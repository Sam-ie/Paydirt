#ifndef FUTURES_H
#define FUTURES_H

#pragma once
#include <QWidget>
#include <QDateTime>
#include "player.h"

namespace Ui {
class Futures;
}

class Futures : public QWidget
{
    Q_OBJECT

public:
    static Futures *instance();

    void do_update();

    //商店等级
    int level;

private:
    explicit Futures(QWidget *parent = nullptr);
    ~Futures();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Futures *ui;

    struct Future_goods
    {
        //商品序号、商品名、商品等级、商品原价、商品现价、商品总数量、玩家持有数量、他人持有数量、商品涨跌情况、历史涨跌情况、购买价格、上次购买时价格
        int     serial_num;
        QString goods;
        int     goods_level;
        double  origin_price;
        double  cur_price;
        int     total_num;
        int     player_num;
        int     others_num;
        double  last_fluctuation;
        double  total_fluctuation;
        double  buy_price;
        double  lowest_buy_price;
    };
    //商店等级
    bool upgrade;
    QList<int> level_need_money;
    //商品列表
    Future_goods fgs[25];
    //填充格式函数
    QString fillFormat (QString str,int maxLen,QString c);
    bool isPositiveInteger(QString str);
    void paddingWindow(Future_goods fg,int place);
    //金额更新
    void paintEvent(QPaintEvent *event) override;
};

#endif // FUTURES_H
