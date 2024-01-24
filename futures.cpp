#include "futures.h"
#include "ui_futures.h"

Futures::Futures(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Futures)
{
    ui->setupUi(this);

    list_goods={"飞机","海景房","游轮","红宝石","钻石",
        "汽车","高档化妆品","高档服装","水晶","工艺品",
        "电脑","黄金","手机","红酒","办公桌",
        "石油","钢材","煤炭","化肥","图书",
        "药品","茶叶","木材","食品","香烟"};

    list_count={10,20,40,60,70,
        20,40,60,100,160,
        40,60,80,160,240,
        50,60,80,100,120,
        150,180,200,250,300};

    list_player_count={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    list_others_count={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    list_price={10000000,5000000,2000000,1000000,800000,
        200000,100000,80000,50000,30000,
        10000,5000,3000,2000,1000,
        800,600,500,300,200,
        100,80,50,30,10};

    list_price_float_rate={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    list_update_cost={};

    list_count_mul_rate={1,4,20,120};

    for (int i=(4-level)*5;i<list_goods.length();i++)
    {
        int cur_count=list_count[i]*list_count_mul_rate[level+std::min(int(i/5),3)-4]-list_player_count[i]-list_others_count[i];
        QString str=FillIn(list_goods[i],5,"  ")+" "+FillIn(QString::number(list_price[i],'f',2),12," ")+" "+
                      FillIn(QString::number(cur_count,'f',0),6," ");
        ui->listWidget->addItem(str);
    }
}

Futures::~Futures()
{
    delete ui;
}

QString Futures::FillIn (QString str,int maxLen,QString c)
{
    int len = str.length();
    if(len < maxLen)
    {
        for(int i =0 ; i < maxLen - len; i++)
            str =  c + str;
    }
    return str;
};

bool Futures::isPositiveInteger(QString str) {
    if (str=="0")
        return false;
    // 正整数正则表达式，不包括前导零
    QRegularExpression regex("^\\d+$");
    return regex.match(str).hasMatch();
}

void Futures::on_pushButton_2_clicked()
{
    // 检查 QListWidget 是否包含被选中的条目
    if (ui->listWidget->selectedItems().isEmpty()) {
        // 如果没有被选中的条目，则不执行任何操作
        return;
    }
    if (ui->lineEdit->text()==""||!isPositiveInteger(ui->lineEdit->text())) {
        ui->lineEdit->setText("0");
        return;
    }

    // 获取被选中的 QListWidgetItem
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    if (!selectedItems.isEmpty()) {
        // 获取被选中的 QListWidgetItem 的文本
        QString selectedText = selectedItems.first()->text();
        // 在这里可以对 selectedText 进行处理或执行其他操作
        QStringList list = selectedText.split(" ");
        list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());

        // 拆分后的第二项（索引为1）转换为浮点数
        float floatValue = list.at(1).toFloat();
        // 拆分后的第三项（索引为2）转换为整数
        int intValue = list.at(2).toInt();
        int num=list_goods.indexOf(list.at(0));

        int sub_num=ui->lineEdit->text().toInt();
        if (sub_num>intValue)
        {
            sub_num=intValue;
            ui->lineEdit->setText(QString::number(sub_num));
        }

        intValue-=sub_num;

        QString str=FillIn(list_goods[num],5,"  ")+" "+FillIn(QString::number(floatValue,'f',2),12," ")+" "+
                      FillIn(QString::number(intValue,'f',0),6," ");
        selectedItems.first()->setText(str);

        list_player_count[num]+=ui->lineEdit->text().toInt();

        str=FillIn(list_goods[num],5,"  ")+" "+FillIn(QString::number(floatValue,'f',2),12," ")+" "+
              FillIn(QString::number(list_player_count[num],'f',0),6," ");

        QList<QListWidgetItem *> items = ui->listWidget_2->findItems("*", Qt::MatchWildcard);
        bool flag=false;
        if (!items.empty())
        {
            foreach(QListWidgetItem *item, items)
            {
                QStringList list = item->text().split(" ");
                list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());
                int num_new=list_goods.indexOf(list.at(0));
                if (num_new==num)
                {
                    flag=true;
                    item->setText(str);
                }
            }
        }
        if (!flag)
        {
            int location=items.length();
            for(int i=0;i<items.length();i++)
            {
                QStringList list = items[i]->text().split(" ");
                list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());
                int num_new=list_goods.indexOf(list.at(0));
                if (num_new>num)
                {
                    location=i;
                    break;
                }
            }
            ui->listWidget_2->insertItem(location,str);
        }

        repaint();
    }
}


void Futures::on_pushButton_3_clicked()
{
    // 检查 QListWidget 是否包含被选中的条目
    if (ui->listWidget_2->selectedItems().isEmpty()) {
        // 如果没有被选中的条目，则不执行任何操作
        return;
    }
    if (ui->lineEdit_2->text()==""||!isPositiveInteger(ui->lineEdit_2->text())) {
        ui->lineEdit_2->setText("0");
        return;
    }

    // 获取被选中的 QListWidgetItem
    QList<QListWidgetItem *> selectedItems = ui->listWidget_2->selectedItems();
    if (!selectedItems.isEmpty()) {
        // 获取被选中的 QListWidgetItem 的文本
        QString selectedText = selectedItems.first()->text();
        // 在这里可以对 selectedText 进行处理或执行其他操作
        QStringList list = selectedText.split(" ");
        list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());

        // 拆分后的第二项（索引为1）转换为浮点数
        float floatValue = list.at(1).toFloat();
        // 拆分后的第三项（索引为2）转换为整数
        int intValue = list.at(2).toInt();
        int num=list_goods.indexOf(list.at(0));

        int sub_num=ui->lineEdit_2->text().toInt();
        if (sub_num>intValue)
        {
            sub_num=intValue;
            ui->lineEdit_2->setText(QString::number(sub_num));
        }

        intValue-=sub_num;

        QString str=FillIn(list_goods[num],5,"  ")+" "+FillIn(QString::number(floatValue,'f',2),12," ")+" "+
                      FillIn(QString::number(intValue,'f',0),6," ");
        if (intValue>0)
            selectedItems.first()->setText(str);
        else
            ui->listWidget_2->takeItem(ui->listWidget_2->row(selectedItems.first()));

        list_player_count[num]=intValue;


        QList<QListWidgetItem *> items = ui->listWidget->findItems("*", Qt::MatchWildcard);
        foreach(QListWidgetItem *item, items)
        {
            QStringList list = item->text().split(" ");
            list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());
            int num_new=list_goods.indexOf(list.at(0));
            int intValue_new = list.at(2).toInt();

            if (num_new==num)
            {
                str=FillIn(list_goods[num],5,"  ")+" "+FillIn(QString::number(floatValue,'f',2),12," ")+" "+
                      FillIn(QString::number(intValue_new+sub_num,'f',0),6," ");
                item->setText(str);
            }
        }

        repaint();
    }
}


void Futures::on_pushButton_4_clicked()
{
    upgrade=true;
}


void Futures::on_pushButton_clicked()
{
    if (upgrade)
    {
        upgrade=false;
        if (level<=4)
        {
            level+=1;
            for (int i=(4-level)*5+4;i>=(4-level)*5;i--)
            {
                int cur_count=list_count[i]*list_count_mul_rate[level+std::min(int(i/5),3)-4]-list_player_count[i]-list_others_count[i];
                QString str=FillIn(list_goods[i],5,"  ")+" "+FillIn(QString::number(list_price[i],'f',2),12," ")+" "+
                              FillIn(QString::number(cur_count,'f',0),6," ");
                ui->listWidget->insertItem(0,str);
            }
            QList<QListWidgetItem *> items = ui->listWidget->findItems("*", Qt::MatchWildcard);
            foreach(QListWidgetItem *item, items)
            {
                QStringList list = item->text().split(" ");
                list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());
                int num_new=list_goods.indexOf(list.at(0));
                float floatValue = list.at(1).toFloat();
                int intValue_new = list.at(2).toInt();

                int cur_count=list_count[num_new]*list_count_mul_rate[level+std::min(int(num_new/5),3)-4]-
                    list_count[num_new]*list_count_mul_rate[level+std::min(int(num_new/5),3)-5]+intValue_new;
                QString str=FillIn(list_goods[num_new],5,"  ")+" "+FillIn(QString::number(floatValue,'f',2),12," ")+" "+
                      FillIn(QString::number(cur_count,'f',0),6," ");
                item->setText(str);
            }
        }
    }
}

