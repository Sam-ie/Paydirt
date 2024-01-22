#include "entrance.h"
#include "ui_entrance.h"

Entrance::Entrance(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Entrance)
{
    ui->setupUi(this);
}

Entrance::~Entrance()
{
    delete ui;
}

void Entrance::on_pushButton_clicked()
{
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
    this->close();
}


void Entrance::on_pushButton_2_clicked()
{
    Help *help = new Help;
    help->show();
}


void Entrance::on_pushButton_3_clicked()
{
    Help *help = new Help;
    help->show();
}


void Entrance::on_pushButton_4_clicked()
{
    Help *help = new Help;
    help->show();
}


void Entrance::on_pushButton_5_clicked()
{
    this->close();
}

