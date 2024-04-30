#include "race.h"
#include <qcontainerfwd.h>


eDeadlyEventType Race::getDeadlyEventWithChance(eDeadlyEventType event, float chance) 
{
    return QRandomGenerator::global()->generateDouble() <= chance ? event : eDeadlyEventType::NONE;
}

Race::Race() 
{
    m_events.push_back(getDeadlyEventWithChance(eDeadlyEventType::DEADLYCHALLENGE, 0.3));
    m_events.push_back(getDeadlyEventWithChance(eDeadlyEventType::DEADLYCHALLENGE, 0.6));
    m_events.push_back(getDeadlyEventWithChance(eDeadlyEventType::LAKE, 1.0));
    m_events.push_back(getDeadlyEventWithChance(eDeadlyEventType::DEADLYCHALLENGE, 0.2));
}
Race::~Race() 
{
}

eDeadlyEventType &Race::operator[](int i) { return m_events[i]; }
const eDeadlyEventType &Race::operator[](int i) const { return m_events.at(i); }

QList<eDeadlyEventType> Race::getEvents() const { return m_events; }

QString Race::toString() const 
{
    QStringList eventList;
    QString str;

    for(const auto c: m_events)
    {
        switch (c) 
        {
            case eDeadlyEventType::NONE:
                eventList.push_back(QString("No challenge"));
                break;
            case eDeadlyEventType::LAKE:
                eventList.push_back(QString("Lake"));
                break;
            case eDeadlyEventType::DEADLYCHALLENGE:
                eventList.push_back(QString("Deadly challenge"));
                break;
        }
    }

    for (const auto c : eventList)
    {
        str += (c + QString("\n"));
    }

    return str;
}