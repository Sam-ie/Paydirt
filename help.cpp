#include "help.h"
#include "ui_help.h"

Help *Help::instance() {
    static Help *instance = nullptr;
    if (!instance) {
        instance = new Help();
    }
    return instance;
}

Help::Help(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Help)
{
    ui->setupUi(this);
}

Help::~Help()
{
    delete ui;
}
