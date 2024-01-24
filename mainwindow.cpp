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

