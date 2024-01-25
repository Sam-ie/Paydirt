#ifndef HELP_H
#define HELP_H

#pragma once
#include <QDialog>

namespace Ui {
class Help;
}

class Help : public QDialog
{
    Q_OBJECT

public:
    static Help *instance(QWidget *parent = nullptr);

private:
    explicit Help(QWidget *parent = nullptr);
    ~Help();

private:
    Ui::Help *ui;
};

#endif // HELP_H
