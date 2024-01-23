#include "futures.h"
#include "ui_futures.h"

Futures::Futures(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Futures)
{
    ui->setupUi(this);
}

Futures::~Futures()
{
    delete ui;
}
