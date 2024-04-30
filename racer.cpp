#include "racer.h"



int Racer::m_count = 0;



Racer::Racer(bool isAlive, bool isWaterproof)
    : m_isAlive(isAlive), m_isWaterproof(isWaterproof) 
{
    m_count += 1;
}
Racer::Racer(bool isWaterproof) : Racer(true, isWaterproof) {}
Racer::Racer()
    : Racer(
        QRandomGenerator::global()->generateDouble() <= 0.4 
        ? true 
        : false
    ) 
{}
Racer::~Racer() {}

bool Racer::getState() const { return m_isWaterproof; }
void Racer::setState(bool waterproof) { m_isWaterproof = waterproof; }

void Racer::jesusMoment() { m_isAlive = true; }
void Racer::kill() { m_isAlive = false; }
bool Racer::isAlive() const { return m_isAlive; }

float Racer::getChanceToSurvive() const { return m_chanceToSurvive; }
void Racer::setChanceToSurvive(float chance) { m_chanceToSurvive = chance; }

int Racer::getCountOfRacers() { return m_count; }

QString Racer::toString() const 
{
    QString str = 
        QString("Is Alive = ") 
        + QVariant(m_isAlive).toString() 
        + QString("\n") 
        + QString("Is Waterproof = ") 
        + QVariant(m_isWaterproof).toString();
    return str;
}
