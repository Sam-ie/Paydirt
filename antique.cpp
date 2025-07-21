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

    Item i;
    qDebug() << i.generateAntique(7).item.description;
}

Antique::~Antique()
{
    delete ui;
}

void Antique::on_appraising_clicked()
{

}


void Antique::on_brainwashing_clicked()
{

}


void Antique::on_items_clicked()
{

}


void Antique::on_not_interested_clicked()
{

}


void Antique::on_upper_clicked()
{

}


void Antique::on_lower_clicked()
{

}


void Antique::on_ratio_clicked()
{

}


void Antique::on_agree_clicked()
{

}


void Antique::on_disagree_clicked()
{

}


void Antique::on_hire_clicked()
{

}


void Antique::on_upgrade_clicked()
{

}


void Antique::on_next_week_clicked()
{
    Player::instance()->setRound();
}


void Antique::on_back_clicked()
{
    MainWindow *mainWindow = MainWindow::instance();
    if (this->isMaximized())
    {
        mainWindow->showMaximized();
    }
    else if(this->isFullScreen())
    {
        mainWindow->showFullScreen();
    }
    else
    {
        mainWindow->move(this->pos());
        mainWindow->resize(this->size());
        mainWindow->show();
    }
    this->close();
}

