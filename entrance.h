#ifndef ENTRANCE_H
#define ENTRANCE_H

#include <QWidget>
#include "mainwindow.h"
#include "help.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Entrance;
}
QT_END_NAMESPACE

class Entrance : public QWidget
{
    Q_OBJECT

public:
    Entrance(QWidget *parent = nullptr);
    ~Entrance();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Entrance *ui;
};
#endif // ENTRANCE_H
