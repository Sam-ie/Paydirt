#ifndef FUTURES_H
#define FUTURES_H

#include <QWidget>
#include "player.h"

namespace Ui {
class Futures;
}

class Futures : public QWidget
{
    Q_OBJECT

public:
    static Futures *instance();

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

private:
    Ui::Futures *ui;

    struct Future_goods
    {
        //商品序号、商品名、商品等级、商品价格、商品总数量、玩家持有数量、他人持有数量、商品涨跌情况、历史涨跌情况、购买价格、上次购买时价格
        int     serial_num;
        QString goods;
        int     goods_level;
        double  cur_price;
        int     total_num;
        int     player_num;
        int     others_num;
        double  last_fluctuation;
        double  total_fluctuation;
        double  buy_price;
        double  last_buy_price;
    };
    //商店等级
    int level;
    bool upgrade;
    QList<int> level_need_money;
    //商品列表
    Future_goods fgs[25];
    //填充格式函数
    QString fillFormat (QString str,int maxLen,QString c);
    bool isPositiveInteger(QString str);
    void paddingWindow(Future_goods fg,int place);
};

#endif // FUTURES_H
