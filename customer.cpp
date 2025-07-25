#include "customer.h"

QStringList Customer::nameList = {
    "张三", "李四", "王五", "赵六", "钱七",
    "孙八", "周九", "吴十", "郑十一", "王十二"
};

Customer::Customer() {}

Customer::Client Customer::generateClient(int reputation, int eloquence)
{
    QRandomGenerator* rand = QRandomGenerator::global();
    Client client;

    // 基本属性
    client.name = nameList.at(rand->bounded(nameList.size()));
    client.ability = rand->bounded(101);    // 0-100
    client.greedy = rand->bounded(101);     // 0-100
    client.is_patient = (rand->bounded(10) < 7);   // 70%概率
    client.is_collector = (rand->bounded(10) < 1); // 10%概率
    client.is_seller = (rand->bounded(100) < 60 - itemManager->inventoryRate()*40);
    client.negotiation_available = 3+eloquence/2;
    if (!client.is_patient)
        client.negotiation_available/=2;

    // 处理古董相关逻辑
    if (client.is_seller) {
        // 卖家逻辑
        Item::Antique_goods newAntique = itemManager->generateAntique(reputation);
        itemManager->appendAntique(newAntique);
        client.pick_id = newAntique.id;
        client.estimated_price = calculateEstimatedPrice(newAntique.true_price,client.ability,client.is_seller,client.is_collector,1.0);
        client.highest_price = client.estimated_price * 5;
        client.lowest_price = client.estimated_price * 0.6;
    } else {
        // 买家逻辑
        Item::Antique_goods* antique = itemManager->findAntique(); // 随机获取
        if (antique) {
            client.pick_id = antique->id;
            client.estimated_price = calculateEstimatedPrice(antique->true_price,client.ability,client.is_seller,client.is_collector,1.0);
            client.highest_price = client.estimated_price * 1.6;
            client.lowest_price = client.estimated_price * 0.2;
        } else {
            client.pick_id = -1;
            client.estimated_price = 0;
            client.highest_price = 0;
            client.lowest_price = 0;
        }
    }

    return client;
}

double Customer::calculateEstimatedPrice(double basePrice, int ability, bool isSeller, bool isCollector, double eventFactor)
{
    QRandomGenerator* rand = QRandomGenerator::global();

    // 能力系数计算
    double abilitySquared = ability * ability;
    double abilityLog = (ability == 0) ? 0 :
                            ability * std::log10(ability/1000.0*999 + 1);

    // 计算估值区间
    double minFactor = 1.0 / (2.0 - abilitySquared/10000.0);
    double maxFactor = 2.0 - abilityLog/10000.0;

    // 确保区间有效
    minFactor = qBound(0.1, minFactor, 10.0);
    maxFactor = qBound(0.1, maxFactor, 10.0);

    // 生成随机估值
    double random = rand->generateDouble();
    double factor = minFactor + random * (maxFactor - minFactor);
    double price = basePrice * factor;

    // 应用修正系数
    if (!isSeller && isCollector) {
        price *= 1.5;
    }
    price *= (isSeller ? 0.9 : 1.1);
    price *= eventFactor;

    return price;
}
