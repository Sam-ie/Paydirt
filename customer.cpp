#include "customer.h"

Customer::Customer() {
    // 初始化姓和名的列表
    surnames << "王" << "李" << "张" << "刘" << "陈" << "杨" << "赵" << "黄" << "周" << "吴"
             << "徐" << "孙" << "胡" << "朱" << "高" << "林" << "何" << "郭" << "马" << "罗"
             << "梁" << "宋" << "郑" << "谢" << "韩" << "唐" << "冯" << "于" << "董" << "程"
             << "曹" << "袁" << "邓" << "许" << "沈" << "曾" << "彭" << "吕" << "苏" << "薛";
    names << "艳" << "秀" << "菲" << "明" << "琳" << "宇" << "翔" << "强" << "乐" << "丹"
          << "慧" << "彬" << "威" << "杰" << "诚" << "芳" << "峰" << "文" << "晶" << "超"
          << "俊" << "云" << "勇" << "鑫" << "敏" << "晨" << "钊" << "亮" << "波" << "佳"
          << "志" << "霞" << "宁" << "雯" << "茜" << "荣" << "建" << "娜" << "婧" << "兰"
          << "龙" << "萍" << "伟" << "海" << "锋" << "瑞" << "婷" << "东" << "雄" << "红"
          << "平" << "燕" << "思" << "丽" << "静";
    names << "频若" << "俊杰" << "典扬" << "雪桂" << "晨迈" << "洋连" << "典达" << "真灿"
          << "沃盛" << "达全" << "绍桦" << "轻影" << "庭坚" << "诗琪" << "高明" << "勋诺"
          << "唯俊" << "帆西" << "波翌" << "瑜晓" << "佑圆" << "中常" << "钰运" << "来东"
          << "茜佳" << "策语" << "湖如" << "花江" << "舒萱" << "志风" << "聪开" << "越洲"
          << "璐迅" << "慧敏" << "喜风" << "诗常" << "峻电" << "略勋" << "喜萱" << "宇泉"
          << "同希" << "普復" << "盛典" << "宏亨" << "骏风" << "飞佰" << "彤艳" << "亭盈"
          << "影谦" << "兆常" << "银岳" << "盈帆" << "铭轩" << "星文" << "芹利" << "台虹"
          << "金榕" << "沃谊" << "辉安" << "相元" << "素笑" << "科吉" << "索辉" << "婷朗"
          << "爱旭" << "诗涵" << "兰驰" << "强荒" << "麟科" << "博柏" << "雨泽" << "至名"
          << "风君" << "集修" << "少荷" << "加芳" << "存蒂" << "曼福" << "至途" << "浦雄"
          << "娜复" << "耿茗" << "若曦" << "伟强" << "吉虎" << "麒荷" << "诗曼" << "朋广"
          << "蔚臣" << "佰学" << "赫丹" << "听曙" << "英謙" << "兆安" << "露黄" << "华如"
          << "桂英" << "慕翰" << "蕾皇" << "力智" << "高芬" << "浅全" << "哲琪" << "均营"
          << "经越" << "精贤" << "兆千" << "俊豪" << "集赛" << "珊理" << "啸全" << "沐云"
          << "瑄润" << "艺盈" << "起腾" << "浩骏" << "壹伟" << "速运" << "仑雅" << "复涵"
          << "竹贝" << "峻都" << "安才" << "彦津" << "柏如" << "浩然" << "兼翌" << "士依"
          << "莲狂" << "厚物" << "圣友" << "韬用" << "锋菁" << "韬名" << "虎灿" << "众彬"
          << "佰亦" << "英嘉" << "实渲" << "茗竹" << "品晨" << "梦丰" << "雪维" << "领蔚"
          << "忠特" << "俊熙" << "建华" << "事肖" << "康生" << "柏蒂" << "江扬" << "芳迈"
          << "媛德" << "莲坚" << "月昂" << "典依" << "迎太" << "泓伟" << "湖亿" << "广霆"
          << "宜航" << "志明" << "奇勋" << "钰同" << "舒明" << "骁贝" << "仕银" << "才会"
          << "镇弘" << "聆方" << "用盈" << "仁瑞" << "佳琪" << "衡览" << "庆聆" << "宜辉"
          << "培友" << "图曼" << "曲洋" << "谊睿" << "雨梦" << "鹏兴" << "典乾" << "静淼"
          << "泉时" << "国兰" << "清宇" << "长洋" << "泰兴" << "晟忠" << "盈竹" << "翰用"
          << "睿福" << "湖涛" << "茗才" << "际途" << "登全" << "雪界" << "祥嘉" << "顺桦"
          << "浚骄" << "廷致" << "齐升" << "折仁" << "年纽" << "思彤" << "垒珍" << "露谊"
          << "铭希" << "欣妍" << "文华" << "辉环" << "雪婷" << "若謙" << "迈逸" << "晟庭"
          << "冰治" << "茜勤" << "浩宇" << "芹恩" << "致银" << "丽丽" << "纳讯";


}

Customer::Client Customer::generateClient(int reputation, int eloquence, int luck)
{
    QRandomGenerator* rand = QRandomGenerator::global();
    Client client;

    // 基本属性
    int randomSurnameIndex = rand->bounded(surnames.size());
    int randomNameIndex = rand->bounded(names.size());
    client.name = surnames[randomSurnameIndex]+names[randomNameIndex];

    client.ability = rand->bounded(101);    // 0-100
    client.greedy = rand->bounded(101);     // 0-100
    client.is_patient = rand->bounded(10) < 10-reputation;
    client.is_collector = rand->bounded(100) < 10+luck; // 10%概率
    client.is_seller = rand->bounded(100) < 60 - itemManager.inventoryRate()*40;

    // 处理古董相关逻辑
    if (client.is_seller) {
        // 卖家逻辑
        Item::Antique_goods newAntique = itemManager.generateAntique(reputation);
        itemManager.appendAntique(newAntique);
        client.pick_id = newAntique.id;
        client.estimated_price = calculateEstimatedPrice(newAntique.true_price,client.ability,client.is_seller,client.is_collector,1.0);
        client.highest_price = client.estimated_price * 5;
        client.lowest_price = client.estimated_price * 0.55;
    } else {
        // 买家逻辑
        Item::Antique_goods antique = itemManager.findAntique(); // 随机获取
        if (antique.id!=-1) {
            client.pick_id = antique.id;
            client.estimated_price = calculateEstimatedPrice(antique.true_price,client.ability,client.is_seller,client.is_collector,1.0);
            client.current_price=client.estimated_price;
            client.highest_price = client.estimated_price * 1.7;
            client.lowest_price = client.estimated_price * 0.2;
        } else {
            client.pick_id = -1;
            client.estimated_price = 0;
            client.current_price=client.estimated_price;
            client.highest_price = 0;
            client.lowest_price = 0;
        }
        client.negotiation_available = 3+eloquence/2;
        if (!client.is_patient)
            client.negotiation_available/=2;
        client.deal=false;
    }

    return client;
}

QString Customer::generateDialogue(Client client, bool flag, double quote, int luck)
{
    QRandomGenerator* rand = QRandomGenerator::global();
    if (client.is_seller)
    {
        if (quote>client.highest_price&&quote>client.current_price*(10+client.negotiation_available)/10)
            client.negotiation_available-=2;
        else
            client.negotiation_available-=1;
        if (client.negotiation_available<=0)
        {
            int will = (client.is_patient)?luck:luck/2;
            return (rand->bounded(10)<will)?final_ask_sell[rand->bounded(final_ask_sell.size())]:leave_sell[rand->bounded(leave_sell.size())];
        }
        if (flag)
        {
            return prologue_sell[rand->bounded(prologue_sell.size())];
        }
        else
        {
            return dialogue_sell[rand->bounded(dialogue_sell.size())];
        }
    }
    else
    {
        if (quote<client.lowest_price&&quote<client.current_price*(10-client.negotiation_available)/10)
            client.negotiation_available-=2;
        else
            client.negotiation_available-=1;
        if (client.negotiation_available<=0)
        {
            int will = (client.is_patient)?luck:luck/2;
            return (rand->bounded(10)<will)?final_ask_buy[rand->bounded(final_ask_buy.size())]:leave_buy[rand->bounded(leave_buy.size())];
        }
        if (flag)
        {
            return prologue_buy[rand->bounded(prologue_buy.size())];
        }
        else
        {
            return dialogue_buy[rand->bounded(dialogue_buy.size())];
        }
    }
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
        price *= 1.3;
    }
    price *= (isSeller ? 0.9 : 1.1);
    price *= eventFactor;

    return price;
}
