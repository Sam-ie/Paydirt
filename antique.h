#ifndef ANTIQUE_H
#define ANTIQUE_H

#include <QWidget>

namespace Ui {
class Antique;
}

class Antique : public QWidget
{
    Q_OBJECT

public:
    static Antique *instance();

private:
    explicit Antique(QWidget *parent = nullptr);
    ~Antique();

private:
    Ui::Antique *ui;
};

#endif // ANTIQUE_H
