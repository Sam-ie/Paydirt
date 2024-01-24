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
    cur_money      =3000;
    future_money   =0;
}

double Player::getCur_money() const
{
    return cur_money;
}

void Player::setCur_money(double newCur_money)
{
    cur_money = newCur_money;
}

double Player::getFuture_money() const
{
    return cur_money;
}

void Player::setFuture_money(double newCur_money)
{
    cur_money = newCur_money;
}
