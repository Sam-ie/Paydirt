#ifndef FUTURES_H
#define FUTURES_H

#include <QWidget>

namespace Ui {
class Futures;
}

class Futures : public QWidget
{
    Q_OBJECT

public:
    explicit Futures(QWidget *parent = nullptr);
    ~Futures();

private:
    Ui::Futures *ui;
};

#endif // FUTURES_H
