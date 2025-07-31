#include "entrance.h"
#include "ui_entrance.h"

Entrance *Entrance::instance() {
    static Entrance instance;
    return &instance;
}

void Entrance::set_close()
{
    this->close();
}

Entrance::Entrance(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Entrance)
{
    m_player=Player::instance();
    m_player->setRound();
    pushbutton_1_change=false;

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
    Select_Difficulty *sd=Select_Difficulty::instance(this);
    sd->show();
}


void Entrance::on_pushButton_2_clicked()
{
    Help *help = Help::instance(this);
    help->show();
}


void Entrance::on_pushButton_3_clicked()
{
    Help *help = Help::instance(this);
    help->show();
}


void Entrance::on_pushButton_4_clicked()
{
    this->showFullScreen();
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
            // button->setStyleSheet("QPushButton{outline: none;font-size: 52px;background-color: blue;color: rgb(255, 120, 0);}");
            button->setStyleSheet("QPushButton{outline: none;font-size: 52px;color: rgb(255, 120, 0);}");
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
            // button->setStyleSheet("QPushButton{outline: none;font-size: 52px;background-color: blue;color: rgb(255, 120, 0);}");
            button->setStyleSheet("QPushButton{outline: none;font-size: 52px;color: rgb(255, 120, 0);}");
        }
    }
    return QObject::eventFilter(watched, event);
}


void Entrance::paintEvent(QPaintEvent *event)
{
    if (pushbutton_1_change)
        ui->pushButton_1->setText("继续游戏");
}
