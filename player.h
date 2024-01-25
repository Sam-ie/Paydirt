#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    static Player *instance();

    int getDifficulty() const;
    void setDifficulty(int newdifficulty);
    double getCur_money() const;
    void setCur_money(double newCur_money);
    double getFuture_money() const;
    void setFuture_money(double newFuture_money);
    int getRound() const;
    void setRound(int newround);

private:
    Player();

private:
    int    difficulty;
    double cur_money;
    double future_money;
    int    round;
};

#endif // PLAYER_H
