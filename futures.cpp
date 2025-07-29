#include "futures.h"
#include "ui_futures.h"
#include "mainwindow.h"

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

    //商品序号、商品名、商品等级、商品原价、商品现价、商品总数量、玩家持有数量、他人持有数量、商品涨跌情况、历史涨跌情况、购买价格、历史最低购买价格

    fgs[0]={0,"飞机",5,12000000,12000000,20,0,10,0,0,0,99999999};
    fgs[1]={1,"海景房",5,5000000,5000000,40,0,20,0,0,0,99999999};
    fgs[2]={2,"游轮",5,2000000,2000000,80,0,40,0,0,0,99999999};
    fgs[3]={3,"红宝石",5,1000000,1000000,120,0,60,0,0,0,99999999};
    fgs[4]={4,"钻石",5,800000,800000,140,0,70,0,0,0,99999999};
    fgs[5]={5,"汽车",4,200000,200000,120,0,60,0,0,0,99999999};
    fgs[6]={6,"高档化妆品",4,100000,100000,160,0,80,0,0,0,99999999};
    fgs[7]={7,"高档服装",4,80000,80000,240,0,120,0,0,0,99999999};
    fgs[8]={8,"水晶",4,50000,50000,400,0,200,0,0,0,99999999};
    fgs[9]={9,"工艺品",4,30000,30000,640,0,320,0,0,0,99999999};
    fgs[10]={10,"电脑",3,10000,10000,280,0,140,0,0,0,99999999};
    fgs[11]={11,"黄金",3,5000,5000,480,0,240,0,0,0,99999999};
    fgs[12]={12,"手机",3,3000,3000,640,0,320,0,0,0,99999999};
    fgs[13]={13,"红酒",3,2000,2000,800,0,400,0,0,0,99999999};
    fgs[14]={14,"办公桌",3,1000,1000,1280,0,640,0,0,0,99999999};
    fgs[15]={15,"石油",2,800,800,400,0,200,0,0,0,99999999};
    fgs[16]={16,"钢材",2,600,600,480,0,240,0,0,0,99999999};
    fgs[17]={17,"煤炭",2,500,500,560,0,280,0,0,0,99999999};
    fgs[18]={18,"化肥",2,300,300,800,0,400,0,0,0,99999999};
    fgs[19]={19,"图书",2,200,200,960,0,480,0,0,0,99999999};
    fgs[20]={20,"药品",1,100,100,400,0,200,0,0,0,99999999};
    fgs[21]={21,"茶叶",1,80,80,480,0,240,0,0,0,99999999};
    fgs[22]={22,"木材",1,50,50,640,0,320,0,0,0,99999999};
    fgs[23]={23,"食品",1,30,30,800,0,400,0,0,0,99999999};
    fgs[24]={24,"香烟",1,10,10,2000,0,1000,0,0,0,99999999};

    level=1;
    upgrade=false;
    level_need_money={};

    for (uint i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
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
        QString str=fillFormat(fg.goods,5,"  ")+" "+fillFormat(QString::number(fg.cur_price,'f',2),11," ")+" "+
                      fillFormat(QString::number(fg.total_num*pow(4,std::max(0,level-fg.goods_level))-fg.player_num-fg.others_num,'f',0),6," ")
            +"   "+fillFormat(QString::number(fg.last_fluctuation,'f',2),6," ")+"     "+fillFormat(QString::number(fg.total_fluctuation,'f',2),7," ");
        QList<QListWidgetItem *> items = ui->listWidget->findItems("*", Qt::MatchWildcard);
        if (!items.empty())
        {
            foreach(QListWidgetItem *item, items)
            {
                QStringList list = item->text().split(" ");
                list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());

                int cur_location=0;
                for (uint i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
                {
                    if(list.at(0)==fgs[i].goods)
                    {
                        cur_location=i;
                        break;
                    }
                }
                if (cur_location==cur_serial_num)
                {
                    if (fg.last_fluctuation<=0)
                        item->setData(Qt::FontRole, QColor("green"));
                    if (fg.last_fluctuation>0)
                        item->setData(Qt::FontRole, QColor("red"));
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
        QString str=fillFormat(fg.goods,5,"  ")+" "+fillFormat(QString::number(fg.buy_price,'f',2),11," ")+" "+
                      fillFormat(QString::number(fg.player_num,'f',0),6," ")+" "+fillFormat(QString::number(fg.cur_price,'f',2),11," ")+"    "+fillFormat(QString::number(fg.last_fluctuation,'f',2),6," ");
        QList<QListWidgetItem *> items = ui->listWidget_2->findItems("*", Qt::MatchWildcard);
        if (!items.empty())
        {
            foreach(QListWidgetItem *item, items)
            {
                QStringList list = item->text().split(" ");
                list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());

                int cur_location=0;
                for (uint i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
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
                        if (fg.buy_price>=fg.cur_price)
                            item->setData(Qt::FontRole, QColor("green"));
                        if (fg.buy_price<fg.cur_price)
                            item->setData(Qt::FontRole, QColor("red"));
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

    Player* py=Player::instance();
    // 获取被选中的 QListWidgetItem
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    if (!selectedItems.isEmpty()) {
        // 获取被选中的 QListWidgetItem 的文本
        QString selectedText = selectedItems.first()->text();
        // 在这里可以对 selectedText 进行处理或执行其他操作
        QStringList list = selectedText.split(" ");
        list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());

        int fg_num=0;
        for (uint i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
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
        if (fgs[fg_num].cur_price*sub_num>py->getCur_money())
        {
            sub_num=(int)(py->getCur_money()/fgs[fg_num].cur_price);
            ui->lineEdit->setText(QString::number(sub_num));
        }
        if (sub_num==0)
            return;
        fgs[fg_num].lowest_buy_price=std::min(fgs[fg_num].cur_price,fgs[fg_num].lowest_buy_price);
        fgs[fg_num].buy_price=(fgs[fg_num].buy_price*fgs[fg_num].player_num+fgs[fg_num].cur_price*sub_num)/(fgs[fg_num].player_num+sub_num);
        fgs[fg_num].player_num+=sub_num;
        py->setCur_money(-fgs[fg_num].cur_price*sub_num);
        py->setFuture_money(fgs[fg_num].cur_price*sub_num);

        paddingWindow(fgs[fg_num],1);
        paddingWindow(fgs[fg_num],2);
        update();
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

    Player* py=Player::instance();
    // 获取被选中的 QListWidgetItem
    QList<QListWidgetItem *> selectedItems = ui->listWidget_2->selectedItems();
    if (!selectedItems.isEmpty()) {
        // 获取被选中的 QListWidgetItem 的文本
        QString selectedText = selectedItems.first()->text();
        // 在这里可以对 selectedText 进行处理或执行其他操作
        QStringList list = selectedText.split(" ");
        list.erase(std::remove_if(list.begin(), list.end(), [](const QString &s) { return s.isEmpty(); }), list.end());

        int fg_num=0;
        for (uint i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
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
        py->setCur_money(fgs[fg_num].cur_price*sub_num);
        py->setFuture_money(-fgs[fg_num].cur_price*sub_num);

        paddingWindow(fgs[fg_num],1);
        paddingWindow(fgs[fg_num],2);
        update();
    }
}


void Futures::on_pushButton_4_clicked()
{
    Player* py=Player::instance();
    double cost_money=1250*pow(8,level);
    if (cost_money<py->getCur_money())
    {
        upgrade=true;
        py->setCur_money(-cost_money);
    }
}


void Futures::on_pushButton_clicked()
{
    if (upgrade)
    {
        upgrade=false;
        if (level<5)
        {
            level+=1;
        }
    }
    Player::instance()->setRound();
}

void Futures::on_pushButton_5_clicked()
{
    if (ui->listWidget->selectedItems().isEmpty()) {
        // 如果没有被选中的条目，则不执行任何操作
        return;
    }
    ui->lineEdit->setText("512000");
    on_pushButton_2_clicked();
}


void Futures::on_pushButton_6_clicked()
{
    if (ui->listWidget_2->selectedItems().isEmpty()) {
        // 如果没有被选中的条目，则不执行任何操作
        return;
    }
    ui->lineEdit_2->setText("512000");
    on_pushButton_3_clicked();
}


void Futures::on_pushButton_7_clicked()
{
    MainWindow *mainWindow = MainWindow::instance();
    if (this->isMaximized())
    {
        mainWindow->showMaximized();
    }
    else if(this->isFullScreen())
    {
        mainWindow->showFullScreen();
    }
    else
    {
        mainWindow->move(this->pos()); // 设置位置，使其与主界面对齐
        mainWindow->resize(this->size()); // 设置大小与主界面相同
        mainWindow->show();
    }
    this->close();
}

void Futures::do_update()
{
    Player* py=Player::instance();
    QRandomGenerator generator;
    generator.seed(QDateTime::currentDateTime().toMSecsSinceEpoch());
    for (uint i=0;i<sizeof(fgs)/sizeof(Future_goods);i++)
    {
        if(fgs[i].goods_level<=level)
        {
            //范围0%-5%
            double random_rate = (pow((double)generator.bounded(300000)/100000+1,2)-1)/3;
            double cur_rate = ((double)generator.bounded(2)-0.5)*2*random_rate;
            double total_fluctuation_fix=0;
            if (fgs[i].total_fluctuation>0)
                total_fluctuation_fix=-fgs[i].total_fluctuation/(10+(double)py->getRound()/10);
            else
                total_fluctuation_fix=-fgs[i].total_fluctuation/10;

            cur_rate+=py->getWhole_Market_Fluctuation()+total_fluctuation_fix;
            cur_rate=std::min(std::max(cur_rate,-10.0),10.0);
            py->setFuture_money((double)fgs[i].player_num*fgs[i].cur_price*cur_rate*0.01);
            fgs[i].last_fluctuation=cur_rate;
            fgs[i].cur_price*=(cur_rate+100)/100;
            fgs[i].total_fluctuation=fgs[i].cur_price/fgs[i].origin_price*100-100;
            double others_num_rate=((py->getDifficulty()-1))*fgs[i].last_fluctuation*0.025+0.5;
            fgs[i].others_num=std::min(others_num_rate*fgs[i].total_num,1.0*fgs[i].total_num*pow(4,std::max(0,level-fgs[i].goods_level))-fgs[i].player_num);

            // if (py->getRound()%26==1)
            //     fgs[i].lowest_buy_price=std::min(fgs[i].buy_price,fgs[i].cur_price);
            paddingWindow(fgs[i],1);
            if (fgs[i].player_num>0)
                paddingWindow(fgs[i],2);
        }
    }
    update();
}

void Futures::paintEvent(QPaintEvent *event)
{
    Player* py=Player::instance();
    // 设置字体
    QFont font;
    //font.setFamily("宋体"); // 设置字体为宋体
    font.setPointSize(12); // 设置字号为12
    font.setBold(true); // 设置字体为粗体

    double expected_total_money=pow(1.009,py->getRound())*(6-py->getDifficulty())*1000*pow(0.5,level-1);
    if (py->getCur_money()+py->getFuture_money()<expected_total_money)
        ui->textEdit->setTextColor("green");
    if (py->getCur_money()+py->getFuture_money()>expected_total_money)
        ui->textEdit->setTextColor("red");
    // 设置文本对齐方式
    ui->textEdit->setFont(font); // 设置字体
    ui->textEdit->setAlignment(Qt::AlignVCenter); // 设置居中对齐(无效？)
    QString templatestr="       玩家总资金%1元\n         玩家现金%2元";
    QString str=templatestr.arg(QString::number(py->getCur_money()+py->getFuture_money(),'f',2))
                      .arg(QString::number(py->getCur_money(),'f',2));
    ui->textEdit->setText(str);

    if (py->getWhole_Market_Fluctuation()<0)
        ui->textEdit_2->setTextColor("green");
    if (py->getWhole_Market_Fluctuation()>0)
        ui->textEdit_2->setTextColor("red");
    ui->textEdit_2->setFont(font); // 设置字体
    //ui->textEdit->setAlignment(Qt::AlignVCenter); // 设置居中对齐(无效？)
    templatestr="      宏观经济走势：%1 %";
    str=templatestr.arg(QString::number(py->getWhole_Market_Fluctuation(),'f',2));
    ui->textEdit_2->setText(str);

    if (py->getCur_money()>=1250*pow(8,level)&&level<5&&!upgrade)
        ui->pushButton_4->setEnabled(true);
    else
        ui->pushButton_4->setEnabled(false);
}

