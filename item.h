#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QList>
#include <QRandomGenerator>
#include <list>

class Item
{
public:
    // 删除拷贝构造函数和赋值运算符
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;

    // 获取单例实例
    static Item& instance() {
        static std::unique_ptr<Item> instance(new Item());
        return *instance;
    }

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
        bool       show_fake;
    };

private:
    double    rarity_rate[7]={1,2,5,15,50,200,1000};
    double    status_rate[7]={0.3,0.6,0.8,1,1.3,1.9,3};
    item_name name_list[200];

    int           next_id=1;
    std::list<Antique_goods> antiqueList;  // 古董链表
    int           max_list_size=8;

    Item();
    // 辅助函数：保留指定有效数字
    static double roundToSignificantDigits(double value, int digits) {
        if (value == 0.0) return 0.0;
        double factor = std::pow(10.0, digits - std::ceil(std::log10(std::fabs(value))));
        return std::round(value * factor) / factor;
    }
    // 计算真实价格的辅助函数
    double calculateTruePrice(Antique_goods antique);

public:
    QString   rarity_list[7]={"平凡","普通","稀有","罕见","史诗","传说","神话"};
    QString   status_list[7]={"报废","极差","较差","一般","良好","极佳","完美"};
    int       reputation_to_year[8]={0,10,30,80,200,500,1250,6500};

    // 古董链表操作
    void           appendAntique(Antique_goods antique);         // 在链表末尾添加
    bool           removeAntiqueById(int id);                    // 删除指定id的节点
    Antique_goods  findAntique(int id);                          // 查找并返回物品
    Antique_goods  findAntique();                                // 随机返回物品
    double         inventoryRate();                              // 库存比例


    // 生成古董物品的函数
    Antique_goods generateAntique(int reputation);
    // 修改古董物品的函数
    double modifyAntique(Antique_goods goods);
    // 修改链表最大size
    void changeMaxListSize(int shop_level);

};

#endif // ITEM_H
