#ifndef RACE_H
#define RACE_H
#pragma once



#include <QList>
#include <QRandomGenerator>



enum class eDeadlyEventType
{
    NONE,
    DEADLYCHALLENGE,
    LAKE,
};



class Race
{
private:
    QList<eDeadlyEventType> m_events;

private:
    eDeadlyEventType getDeadlyEventWithChance(eDeadlyEventType event, float chance);

public:
    Race();
    ~Race();

public:
    eDeadlyEventType &operator[](int i);
    const eDeadlyEventType &operator[](int i) const;

public:
    QList<eDeadlyEventType> getEvents() const;

public:
    QString toString() const;

};

#endif // RACE_H
