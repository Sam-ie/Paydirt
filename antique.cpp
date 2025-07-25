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
    updateAntique();
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

void Antique::updateAntique()
{
    // 1. 生成新的古董物品
    Item::Antique_goods newAntique = itemGenerator.generateAntique(reputation);

    // 3. 准备要显示的文本
    QString AntiqueString = QString("%1\t 年的 %2\n"
                               "%3 %4\t 估价: %5\n")
                           .arg((newAntique.year<0)?("公元前"+QString::number(-newAntique.year)):("公元  "+QString::number(newAntique.year)))
                           .arg(newAntique.item.item_type)
                           .arg(itemGenerator.status_list[newAntique.status])
                           .arg(newAntique.is_fake?(newAntique.show_fake?"假货":"真货"):"真货")
                           .arg(newAntique.estimated_price, 0, 'f', 2);

    // 4. 添加到文本浏览器
    ui->text_antique->setText(AntiqueString);

    // 5. 自动滚动到底部
    ui->text_antique->verticalScrollBar()->setValue(
        ui->text_antique->verticalScrollBar()->maximum()
        );
}
