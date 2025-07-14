#include "lottery.h"
#include "ui_lottery.h"

Lottery *Lottery::instance() {
    static Lottery *instance = nullptr;
    if (!instance) {
        instance = new Lottery();
    }
    return instance;
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
