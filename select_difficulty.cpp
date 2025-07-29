#include "select_difficulty.h"
#include "ui_select_difficulty.h"
#include "entrance.h"
#include "mainwindow.h"

Select_Difficulty *Select_Difficulty::instance(QWidget *parent) {
    static Select_Difficulty *instance = nullptr;
    if (!instance) {
        instance = new Select_Difficulty(parent);
    }
    return instance;
}

Select_Difficulty::Select_Difficulty(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Select_Difficulty)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
}

Select_Difficulty::~Select_Difficulty()
{
    delete ui;
}

void Select_Difficulty::on_pushButton_1_clicked()
{
    Player::instance()->setDifficulty(1);
    MainWindow *mainWindow = MainWindow::instance();
    if (Entrance::instance()->isMaximized())
    {
        mainWindow->showMaximized();
    }
    else if(Entrance::instance()->isFullScreen())
    {
        mainWindow->showFullScreen();
    }
    else
    {
        mainWindow->move(Entrance::instance()->pos()); // 设置位置，使其与主界面对齐
        mainWindow->resize(Entrance::instance()->size()); // 设置大小与主界面相同
        mainWindow->show();
    }
    this->close();
    Entrance::instance()->set_close();
    Entrance::instance()->pushbutton_1_change=true;
}


void Select_Difficulty::on_pushButton_2_clicked()
{
    Player::instance()->setDifficulty(2);
    MainWindow *mainWindow = MainWindow::instance();
    if (Entrance::instance()->isMaximized())
    {
        mainWindow->showMaximized();
    }
    else if(Entrance::instance()->isFullScreen())
    {
        mainWindow->showFullScreen();
    }
    else
    {
        mainWindow->move(Entrance::instance()->pos()); // 设置位置，使其与主界面对齐
        mainWindow->resize(Entrance::instance()->size()); // 设置大小与主界面相同
        mainWindow->show();
    }
    this->close();
    Entrance::instance()->set_close();
    Entrance::instance()->pushbutton_1_change=true;
}


void Select_Difficulty::on_pushButton_3_clicked()
{
    Player::instance()->setDifficulty(3);
    MainWindow *mainWindow = MainWindow::instance();
    if (Entrance::instance()->isMaximized())
    {
        mainWindow->showMaximized();
    }
    else if(Entrance::instance()->isFullScreen())
    {
        mainWindow->showFullScreen();
    }
    else
    {
        mainWindow->move(Entrance::instance()->pos()); // 设置位置，使其与主界面对齐
        mainWindow->resize(Entrance::instance()->size()); // 设置大小与主界面相同
        mainWindow->show();
    }
    this->close();
    Entrance::instance()->set_close();
    Entrance::instance()->pushbutton_1_change=true;
}


void Select_Difficulty::on_pushButton_4_clicked()
{
    this->close();
}

