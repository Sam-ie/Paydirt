#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QRandomGenerator>
#include "item.h"
#include "attribute.h"


class Customer
{
public:
    // 删除拷贝构造函数和赋值运算符
    Customer(const Customer&) = delete;
    Customer& operator=(const Customer&) = delete;

    // 获取单例实例
    static Customer& instance() {
        static Customer instance;
        return instance;
    }

    struct Client
    {

        QString name;
        int     ability;
        int     greedy;
        bool    is_patient;
        bool    is_collector;
        bool    is_seller;
        int     pick_id;
        double  estimated_price;
        double  current_price;
        double  highest_price;
        double  lowest_price;
        int     negotiation_available;
        bool    deal;
    };

    // 生成顾客的函数
    Client generateClient();

    QString generateDialogue(Customer::Client, bool flag, double quote);// 0为初始化，1为继续


private:
    QList<QString> names;  // 名字列表
    QList<QString> surnames;  // 姓氏列表
    QList<QString> prologue_sell;
    QList<QString> prologue_buy;
    QList<QString> dialogue_sell;
    QList<QString> dialogue_buy;
    QList<QString> leave_sell;
    QList<QString> leave_buy;
    QList<QString> final_ask_sell;
    QList<QString> final_ask_buy;
    QList<QString> deal_sell;
    QList<QString> deal_buy;

    Item& itemManager = Item::instance();
    Attribute& attribute = Attribute::instance();

    Customer();
    double calculateEstimatedPrice(double basePrice, int ability, bool isSeller, bool isCollector, double eventFactor);

};

#endif // CUSTOMER_H
