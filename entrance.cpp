#include "entrance.h"
#include "ui_entrance.h"

Entrance::Entrance(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Entrance)
{
    // QPushButton *button1 = new QPushButton("pushButton_1", this);
    // button1->setFocusPolicy(Qt::NoFocus);

    // QPushButton *button2 = new QPushButton("pushButton_2", this);
    // button2->setFocusPolicy(Qt::NoFocus);

    // QPushButton *button3 = new QPushButton("pushButton_3", this);
    // button3->setFocusPolicy(Qt::NoFocus);

    // QPushButton *button4 = new QPushButton("pushButton_4", this);
    // button4->setFocusPolicy(Qt::NoFocus);

    // QPushButton *button5 = new QPushButton("pushButton_5", this);
    // button5->setFocusPolicy(Qt::NoFocus);

    ui->setupUi(this);

    ui->pushButton_1->installEventFilter(this);
    ui->pushButton_2->installEventFilter(this);
    ui->pushButton_3->installEventFilter(this);
    ui->pushButton_4->installEventFilter(this);
    ui->pushButton_5->installEventFilter(this);
}

Entrance::~Entrance()
{
    delete ui;
}

void Entrance::on_pushButton_1_clicked()
{
    MainWindow *mainWindow = new MainWindow;
    if (this->isMaximized())
    {
        mainWindow->showMaximized();
    }
    else
    {
        mainWindow->move(this->pos()); // 设置位置，使其与主界面对齐
        mainWindow->resize(this->size()); // 设置大小与主界面相同
        mainWindow->show();
    }
    this->close();
}


void Entrance::on_pushButton_2_clicked()
{
    Help *help = new Help;
    help->show();
}


void Entrance::on_pushButton_3_clicked()
{
    Help *help = new Help;
    help->show();
}


void Entrance::on_pushButton_4_clicked()
{
    Help *help = new Help;
    help->show();
}


void Entrance::on_pushButton_5_clicked()
{
    this->close();
}


bool Entrance::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        QPushButton *button = qobject_cast<QPushButton *>(watched);
        if (button)
        {
            // 改变按钮样式，例如改变背景色
            // button->setStyleSheet("QPushButton{outline: none;font-size: 55px;background-color: blue;color: rgb(255, 120, 0);}");
            button->setStyleSheet("QPushButton{outline: none;font-size: 55px;color: rgb(255, 120, 0);}");
        }
    } else if (event->type() == QEvent::FocusOut)
    {
        // 当焦点离开时，可以重置样式或恢复默认样式
        QPushButton *button = qobject_cast<QPushButton *>(watched);
        if (button)
        {
            button->setStyleSheet("QPushButton{color: rgb(255, 230, 0);border: none;}");
        }
    } else if (event->type() == QEvent::HoverEnter)
    {
        // 当焦点离开时，可以重置样式或恢复默认样式
        QPushButton *button = qobject_cast<QPushButton *>(watched);
        for (int i = 0; i < 5; ++i)
        {
            QPushButton *button = findChild<QPushButton *>("pushButton_" + QString::number(i));
            if (button)
            {
                button->clearFocus();
            }
        }
        button->setFocus();
        if (button)
        {
            // button->setStyleSheet("QPushButton{outline: none;font-size: 55px;background-color: blue;color: rgb(255, 120, 0);}");
            button->setStyleSheet("QPushButton{outline: none;font-size: 55px;color: rgb(255, 120, 0);}");
        }
    }
    return QObject::eventFilter(watched, event);
}

