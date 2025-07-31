#include "lottery.h"
#include "ui_lottery.h"
#include "mainwindow.h"

Lottery *Lottery::instance() {
    static Lottery instance;
    return &instance;
}

Lottery::Lottery(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Lottery)
{
    ui->setupUi(this);
}

Lottery::~Lottery()
{
    delete ui;
}
