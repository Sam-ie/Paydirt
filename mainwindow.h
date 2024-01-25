#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QWidget>
#include "futures.h"
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    static MainWindow *instance();

private:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QList<QString> difficulty_name;
};

#endif // MAINWINDOW_H
