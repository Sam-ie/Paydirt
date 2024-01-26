#include "player.h"

Player *Player::instance() {
    static Player *instance = nullptr;
    if (!instance) {
        instance = new Player();
    }
    return instance;
}

Player::Player()
{
    difficulty               =0;
    cur_money                =6000;
    future_money             =0;
    round                    =0;
    whole_market_fluctuation =0;
}

int Player::getDifficulty() const
{
    return difficulty;
}

void Player::setDifficulty(int newdifficulty)
{
    this->difficulty = newdifficulty;
    cur_money-=1000*difficulty;
}

double Player::getCur_money() const
{
    return cur_money;
}

void Player::setCur_money(double newCur_money)
{
    cur_money += newCur_money;
}

double Player::getFuture_money() const
{
    return future_money;
}

void Player::setFuture_money(double newfuture_money)
{
    future_money += newfuture_money;
}

int Player::getRound() const
{
    return round;
}

void Player::setRound()
{
    round++;
    if (round%8==1)
    {
        QRandomGenerator generator;
        generator.seed(QDateTime::currentDateTime().toMSecsSinceEpoch());
        int random_rate = generator.bounded(800000)-100000*(difficulty+2);
        //对应-2%——6% -3%——5% -4%——4% (1.04*0.96<1)
        whole_market_fluctuation = (double)random_rate/100000;
    }
    Futures::instance()->do_update();
}

double Player::getWhole_Market_Fluctuation() const
{
    return whole_market_fluctuation;
}
