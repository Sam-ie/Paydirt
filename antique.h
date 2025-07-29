#ifndef ANTIQUE_H
#define ANTIQUE_H

#include <QWidget>
#include <QScrollBar>
#include "item.h"
#include "customer.h"
#include "attribute.h"

namespace Ui {
class Antique;
}

class Antique : public QWidget
{
    Q_OBJECT

public:
    static Antique *instance();

private slots:
    void on_appraising_clicked();
    void on_brainwashing_clicked();
    void on_items_clicked();
    void on_not_interested_clicked();
    void on_upper_clicked();
    void on_lower_clicked();
    void on_ratio_clicked();
    void on_agree_clicked();
    void on_disagree_clicked();
    void on_hire_clicked();
    void on_upgrade_clicked();
    void on_next_week_clicked();
    void on_back_clicked();

private:
    explicit Antique(QWidget *parent = nullptr);
    ~Antique();
    Ui::Antique *ui;

    void updateAntique();
    void initClient();
    void updateDialogue();


private:
    // 报价
    double quote;

    Attribute& attribute = Attribute::instance();
    Customer& clientGenerator = Customer::instance();
    Item& itemGenerator = Item::instance();
    Customer::Client newClient;

};

#endif // ANTIQUE_H
