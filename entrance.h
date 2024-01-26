#ifndef ENTRANCE_H
#define ENTRANCE_H

#pragma once
#include <QWidget>
#include "select_difficulty.h"
#include "help.h"
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Entrance;
}
QT_END_NAMESPACE

class Entrance : public QWidget
{
    Q_OBJECT

public:
    static Entrance *instance();

    bool pushbutton_1_change;

    void set_close();

private:
    Entrance(QWidget *parent = nullptr);
    ~Entrance();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Entrance *ui;

    bool eventFilter(QObject *watched, QEvent *event);
};
#endif // ENTRANCE_H
