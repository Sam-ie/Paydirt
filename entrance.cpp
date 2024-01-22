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
