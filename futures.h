#ifndef FUTURES_H
#define FUTURES_H

#include <QWidget>

namespace Ui {
class Futures;
struct Future_goods
{
    //商品名、商品价格、商品总数量、玩家持有数量、他人持有数量、商品涨跌情况、历史涨跌情况、购买价格、上次购买时价格
    QString goods;
    float   cur_price;
    int     total_num;
    int     palyer_num;
    int     others_num;
    float   last_fluctuation;
    float   total_fluctuation;
    float   buy_price;
    float   last_buy_price;
};
}

class Futures : public QWidget
{
    Q_OBJECT

public:
    explicit Futures(QWidget *parent = nullptr);
    ~Futures();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::Futures *ui;

    int level=1;

    QList<QString> list_goods;
    QList<int> list_count;
    QList<int> list_player_count;
    QList<int> list_others_count;
    QList<float> list_price;
    QList<float> list_price_float_rate;
    QList<float> list_update_cost;
    QList<int> list_count_mul_rate;

    float cur_money=3000;
    float sum_money=3000;

    bool upgrade=false;

    QString FillIn (QString str,int maxLen,QString c);
    bool isPositiveInteger(QString str);
};

#endif // FUTURES_H
