#ifndef SELECT_DIFFICULTY_H
#define SELECT_DIFFICULTY_H

#pragma once
#include <QWidget>

namespace Ui {
class Select_Difficulty;
}

class Select_Difficulty : public QWidget
{
    Q_OBJECT

public:
    static Select_Difficulty *instance(QWidget *parent = nullptr);

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    explicit Select_Difficulty(QWidget *parent = nullptr);
    ~Select_Difficulty();

private:
    Ui::Select_Difficulty *ui;
};

#endif // SELECT_DIFFICULTY_H
