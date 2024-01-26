#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow *MainWindow::instance() {
    static MainWindow *instance = nullptr;
    if (!instance) {
        instance = new MainWindow();
    }
    return instance;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    difficulty_name={"","简单","普通","困难"};

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Futures *futures = Futures::instance();
    if (this->isMaximized())
    {
        futures->showMaximized();
    }
    else if(this->isFullScreen())
    {
        futures->showFullScreen();
    }
    else
    {
        futures->move(this->pos()); // 设置位置，使其与主界面对齐
        futures->resize(this->size()); // 设置大小与主界面相同
        futures->show();
    }
    this->close();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Player* py=Player::instance();
    // 设置字体
    QFont font;
    //font.setFamily("华文楷体"); // 设置字体(太慢)
    font.setPointSize(20); // 设置字号为24
    font.setBold(true); // 设置字体为粗体

    // 设置文本对齐方式
    ui->textEdit->setFont(font); // 设置字体
    //ui->textEdit->setAlignment(Qt::AlignVCenter); // 设置居中对齐(无效？)
    QString templatestr="                                    目标：\n              30年内挣够一个小目标(1亿元)\n                              难度：%1\n"
                          "               玩家总资金：%2 元\n                   玩家现金：%3 元\n                       现在是第 %4 年 %5 月";
    QString str=templatestr.arg(difficulty_name[py->getDifficulty()])
                      .arg(QString::number(py->getCur_money()+py->getFuture_money(),'f',2))
                      .arg(QString::number(py->getCur_money(),'f',2))
                      .arg(py->getRound()/52+1).arg((int)((double)(py->getRound()%52)*3/13)+1);
    ui->textEdit->setText(str);

    if (py->getWhole_Market_Fluctuation()<0)
        ui->textEdit_2->setTextColor("green");
    if (py->getWhole_Market_Fluctuation()>0)
        ui->textEdit_2->setTextColor("red");
    ui->textEdit_2->setFont(font); // 设置字体
    templatestr="                       宏观经济：%1%\n";
    str=templatestr.arg(py->getWhole_Market_Fluctuation());
    ui->textEdit_2->setText(str);
}

void MainWindow::on_pushButton_2_clicked()
{
    Help *help = Help::instance(this);
    help->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    Help *help = Help::instance(this);
    help->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    Player::instance()->setRound();
    update();
}


void MainWindow::on_pushButton_5_clicked()
{
    Entrance *entrance = Entrance::instance();
    if (this->isMaximized())
    {
        entrance->showMaximized();
    }
    else if(this->isFullScreen())
    {
        entrance->showFullScreen();
    }
    else
    {
        entrance->move(this->pos()); // 设置位置，使其与主界面对齐
        entrance->resize(this->size()); // 设置大小与主界面相同
        entrance->show();
    }
    this->close();
}

