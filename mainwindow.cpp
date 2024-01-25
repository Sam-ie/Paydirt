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
    // 设置字体
    QFont font;
    font.setFamily("宋体"); // 设置字体为宋体
    font.setPointSize(20); // 设置字号为20
    font.setBold(true); // 设置字体为粗体

    // 设置文本对齐方式
    ui->textEdit->setFont(font); // 设置字体
    //ui->textEdit->setAlignment(Qt::AlignVCenter); // 设置居中对齐(无效？)
    QString templatestr="                  目标：\n       40年内挣够一个小目标(1亿元)\n               难度：%1\n"
                          "      玩家总资金：%2 元\n         玩家现金：%3 元\n           现在是第 %4 年 %5 月";
    QString str=templatestr.arg(difficulty_name[Player::instance()->getDifficulty()])
                      .arg(QString::number(Player::instance()->getCur_money()+Player::instance()->getFuture_money(),'f',2))
                      .arg(QString::number(Player::instance()->getCur_money(),'f',2))
                      .arg(Player::instance()->getRound()/12+1).arg(Player::instance()->getRound()%12+1);
    ui->textEdit->setText(str);
}
