#ifndef RACER_H
#define RACER_H
#pragma once



#include <QString>
#include <QVariant>
#include <QRandomGenerator>



class Racer
{
private:
    static int m_count;
    bool m_isAlive = 0;
    bool m_isWaterproof = 0;
    float m_chanceToSurvive = 0.0;

public:
    Racer(bool isDead, bool isWaterproof);
    Racer(bool isWaterproof);
    Racer();
    ~Racer();

public:
    bool getState() const;
    void setState(bool waterproof);

    void jesusMoment();
    void kill();
    bool isAlive() const;

    float getChanceToSurvive() const;
    void setChanceToSurvive(float chance);

    static int getCountOfRacers();

public:
    QString toString() const;

};

#endif // RACER_H
