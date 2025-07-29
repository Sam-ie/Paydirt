#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>
#include <QRandomGenerator>

class Attribute
{
public:
    // 删除拷贝构造函数和赋值运算符
    Attribute(const Attribute&) = delete;
    Attribute& operator=(const Attribute&) = delete;

    // 获取单例实例
    static Attribute& instance() {
        static std::unique_ptr<Attribute> instance(new Attribute());
        return *instance;
    }

    // 玩家
    int    eloquence;
    int    ability;
    int    insight;
    int    luck;
    int    shop_level;
    int    reputation; // 注意reputation对应reputation_list时要-1

    QString getAttributeText();

private:
    Attribute();

    QString   reputation_list[7]={"默默无闻","口碑尚可","小有名气","有口皆碑","名噪一时","誉满天下","名垂青史"};
    QString   shop_level_list[20]={"破旧地摊","三轮小铺","便宜坊","旧物拾荒","旧梦回收站",
                                   "拾光杂货","拾趣小铺","手作小集","巷陌物语","微光工坊",
                                   "艺术一角","素年集物","时光刻度","山隅小筑","墨痕工坊",
                                   "观物集","栖物志","一方归处","未名美术馆","无界之境"};

};

#endif // ATTRIBUTE_H
