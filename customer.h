#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QRandomGenerator>
#include "item.h"


class Customer
{
public:
    Customer();

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
        double  highest_price;
        double  lowest_price;
        int     negotiation_available;
    };

    // 生成顾客的函数
    Client generateClient(int reputation, int eloquence);



private:
    static QStringList nameList;

    Item* itemManager;

    double calculateEstimatedPrice(double basePrice, int ability, bool isSeller, bool isCollector, double eventFactor);

};

#endif // CUSTOMER_H
