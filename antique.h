#ifndef ANTIQUE_H
#define ANTIQUE_H

#include <QWidget>
#include "mainwindow.h"
#include "item.h"

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

private:
    Ui::Antique *ui;

    struct customer
    {
        QString name;
        int     ability;
        int     greedy;
        bool    is_patient;
        bool    is_collector;
        int     pick_id;
        double  estimated_price;
        double  highest_price;
        double  lowest_price;
    };

private:
    // 玩家
    int    eloquence;
    int    ability;
    int    insight;
    int    luck;
    int    shop_level;
    int    reputation;

};

#endif // ANTIQUE_H
