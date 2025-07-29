#ifndef LOTTERY_H
#define LOTTERY_H

#include <QWidget>
#include "player.h"

namespace Ui {
class Lottery;
}

class Lottery : public QWidget
{
    Q_OBJECT

public:
    static Lottery *instance();

private:
    explicit Lottery(QWidget *parent = nullptr);
    ~Lottery();

private:
    Ui::Lottery *ui;
};

#endif // LOTTERY_H
