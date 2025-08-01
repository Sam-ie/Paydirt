#include "help.h"
#include "ui_help.h"

Help *Help::instance(QWidget *parent) {
    static Help instance;
    return &instance;
}

Help::Help(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Help)
{
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);

    ui->setupUi(this);
}

Help::~Help()
{
    delete ui;
}
