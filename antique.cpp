#include "antique.h"
#include "ui_antique.h"

Antique *Antique::instance() {
    static Antique *instance = nullptr;
    if (!instance) {
        instance = new Antique();
    }
    return instance;
}

Antique::Antique(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Antique)
{
    ui->setupUi(this);
}

Antique::~Antique()
{
    delete ui;
}
