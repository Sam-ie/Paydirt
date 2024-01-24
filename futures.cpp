#include "futures.h"
#include "ui_futures.h"

Futures *Futures::instance() {
    static Futures *instance = nullptr;
    if (!instance) {
        instance = new Futures();
    }
    return instance;
}

Futures::Futures(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Futures)
{
    ui->setupUi(this);

    //商品序号、商品名、商品等级、商品价格、商品总数量、玩家持有数量、他人持有数量、商品涨跌情况、历史涨跌情况、购买价格、上次购买时价格

    fgs[0]={0,"飞机",5,10000000,10,0,0,0,0,0,0};
    fgs[1]={1,"海景房",5,5000000,20,0,0,0,0,0,0};
    fgs[2]={2,"游轮",5,2000000,40,0,0,0,0,0,0};
    fgs[3]={3,"红宝石",5,1000000,60,0,0,0,0,0,0};
    fgs[4]={4,"钻石",5,800000,70,0,0,0,0,0,0};
    fgs[5]={5,"汽车",4,200000,60,0,0,0,0,0,0};
    fgs[6]={6,"高档化妆品",4,100000,80,0,0,0,0,0,0};
    fgs[7]={7,"高档服装",4,80000,120,0,0,0,0,0,0};
    fgs[8]={8,"水晶",4,50000,200,0,0,0,0,0,0};
    fgs[9]={9,"工艺品",4,30000,320,0,0,0,0,0,0};
    fgs[10]={10,"电脑",3,10000,140,0,0,0,0,0,0};
    fgs[11]={11,"黄金",3,5000,240,0,0,0,0,0,0};
    fgs[12]={12,"手机",3,3000,320,0,0,0,0,0,0};
    fgs[13]={13,"红酒",3,2000,400,0,0,0,0,0,0};
    fgs[14]={14,"办公桌",3,1000,640,0,0,0,0,0,0};
    fgs[15]={15,"石油",2,800,200,0,0,0,0,0,0};
    fgs[16]={16,"钢材",2,600,240,0,0,0,0,0,0};
    fgs[17]={17,"煤炭",2,500,280,0,0,0,0,0,0};
    fgs[18]={18,"化肥",2,300,400,0,0,0,0,0,0};
    fgs[19]={19,"图书",2,200,480,0,0,0,0,0,0};
    fgs[20]={20,"药品",1,100,200,0,0,0,0,0,0};
    fgs[21]={21,"茶叶",1,80,240,0,0,0,0,0,0};
    fgs[22]={22,"木材",1,50,320,0,0,0,0,0,0};
    fgs[23]={23,"食品",1,30,400,0,0,0,0,0,0};
    fgs[24]={24,"香烟",1,10,1000,0,0,0,0,0,0};

    level=1;
    upgrade=false;
    level_need_money={};

    for (int i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
    {
        if(fgs[i].goods_level<=level)
            paddingWindow(fgs[i],1);
    }
}

Futures::~Futures()
{
    delete ui;
}

QString Futures::fillFormat (QString str,int maxLen,QString c)
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

void Futures::paddingWindow(Future_goods fg, int place)
{
    int cur_serial_num=fg.serial_num;
    int location=0;
    if (place==1)
    {
        QString str=fillFormat(fg.goods,5,"  ")+" "+fillFormat(QString::number(fg.cur_price,'f',2),12," ")+" "+
                      fillFormat(QString::number(fg.total_num*pow(4,std::max(0,level-fg.goods_level))-fg.player_num-fg.others_num,'f',0),6," ");
        QList<QListWidgetItem *> items = ui->listWidget->findItems("*", Qt::MatchWildcard);
        if (!items.empty())
        {
            foreach(QListWidgetItem *item, items)
            {
                QStringList list = item->text().split(" ");
                list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());

                int cur_location=0;
                for (int i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
                {
                    if(list.at(0)==fgs[i].goods)
                    {
                        cur_location=i;
                        break;
                    }
                }
                if (cur_location==cur_serial_num)
                {
                    item->setText(str);
                    return;
                }
                if (cur_location>cur_serial_num)
                {
                    ui->listWidget->insertItem(location,str);
                    return;
                }
                location++;
            }
        }
        ui->listWidget->addItem(str);
    }
    else if (place==2)
    {
        QString str=fillFormat(fg.goods,5,"  ")+" "+fillFormat(QString::number(fg.cur_price,'f',2),12," ")+" "+
                      fillFormat(QString::number(fg.player_num,'f',0),6," ");
        QList<QListWidgetItem *> items = ui->listWidget_2->findItems("*", Qt::MatchWildcard);
        if (!items.empty())
        {
            foreach(QListWidgetItem *item, items)
            {
                QStringList list = item->text().split(" ");
                list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());

                int cur_location=0;
                for (int i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
                {
                    if(list.at(0)==fgs[i].goods)
                    {
                        cur_location=i;
                        break;
                    }
                }
                if (cur_location==cur_serial_num)
                {
                    if (fg.player_num==0)
                    {
                        ui->listWidget_2->takeItem(ui->listWidget_2->row(item));
                    }
                    else
                    {
                        item->setText(str);
                        ui->listWidget_2->setCurrentItem(item);
                    }
                    return;
                }
                if (cur_location>cur_serial_num)
                {
                    ui->listWidget_2->insertItem(location,str);
                    ui->listWidget_2->setCurrentRow(location);
                    return;
                }
                location++;
            }
        }
        ui->listWidget_2->addItem(str);
        ui->listWidget_2->setCurrentRow(location);
    }
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

        int fg_num;
        for (int i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
        {
            if(list.at(0)==fgs[i].goods)
            {
                fg_num=i;
                break;
            }
        }

        int sub_num=ui->lineEdit->text().toInt();
        if (sub_num>fgs[fg_num].total_num*pow(4,std::max(0,level-fgs[fg_num].goods_level))-fgs[fg_num].player_num-fgs[fg_num].others_num)
        {
            sub_num=fgs[fg_num].total_num*pow(4,std::max(0,level-fgs[fg_num].goods_level))-fgs[fg_num].player_num-fgs[fg_num].others_num;
            ui->lineEdit->setText(QString::number(sub_num));
        }
        fgs[fg_num].player_num+=sub_num;

        paddingWindow(fgs[fg_num],1);
        paddingWindow(fgs[fg_num],2);
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

        int fg_num;
        for (int i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
        {
            if(list.at(0)==fgs[i].goods)
            {
                fg_num=i;
                break;
            }
        }

        int sub_num=ui->lineEdit_2->text().toInt();
        if (sub_num>fgs[fg_num].player_num)
        {
            sub_num=fgs[fg_num].player_num;
            ui->lineEdit_2->setText(QString::number(sub_num));
        }

        fgs[fg_num].player_num-=sub_num;

        paddingWindow(fgs[fg_num],1);
        paddingWindow(fgs[fg_num],2);
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
        if (level<5)
        {
            level+=1;
            for (int i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
            {
                if(fgs[i].goods_level<=level)
                    paddingWindow(fgs[i],1);
            }
            repaint();
        }
    }
}

void Futures::on_pushButton_5_clicked()
{
    ui->lineEdit->setText("256000");
    on_pushButton_2_clicked();
}


void Futures::on_pushButton_6_clicked()
{
    ui->lineEdit_2->setText("256000");
    on_pushButton_3_clicked();
}

