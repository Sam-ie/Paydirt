#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    static Player *instance();

    double getCur_money() const;
    void setCur_money(double newCur_money);
    double getFuture_money() const;
    void setFuture_money(double newFuture_money);

private:
    Player();

private:
    double cur_money;
    double future_money;
};

#endif // PLAYER_H
