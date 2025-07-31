#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <QRandomGenerator>
#include <QDateTime>
#include <QJsonObject>
#include <QSaveFile>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>

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
    void setRound();
    double getWhole_Market_Fluctuation() const;

    // 获取JSON文件路径（静态方法，全局可访问）
    static QString getJsonFilePath() {
        static const QString path = [](){
            QString localLowPath = QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/../LocalLow");
            QString fullPath = localLowPath + "/Alfie Brook/Paydirt/data.json";
            return QDir::toNativeSeparators(fullPath);
        }();
        return path;
    }
    // JSON 操作
    void saveToJson();
    void loadFromJson();

private:
    Player();
    ~Player();


private:
    int    difficulty;
    double cur_money;
    double future_money;
    int    round;
    double whole_market_fluctuation;
};

#endif // PLAYER_H
