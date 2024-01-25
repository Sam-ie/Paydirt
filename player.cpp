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
    difficulty     =0;
    cur_money      =6000;
    future_money   =0;
    round          =0;
}

int Player::getDifficulty() const
{
    return difficulty;
}

void Player::setDifficulty(int newdifficulty)
{
    difficulty = newdifficulty;
    cur_money-=1000*difficulty;
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
    return future_money;
}

void Player::setFuture_money(double newfuture_money)
{
    cur_money = newfuture_money;
}

int Player::getRound() const
{
    return round;
}

void Player::setRound(int newround)
{
    round = newround;
}
