#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "race.h"
#include "racer.h"
#include <cmath>
#include <qabstractitemmodel.h>
#include <qcontainerfwd.h>
#include <qdebug.h>
#include <qobjectdefs.h>



void MainWindow::setupModel() 
{
    ui->lv_racersList->setModel(m_model);
}





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        this,
        SIGNAL(racerListChanged()), 
        this, 
        SLOT(on_moduleUpdate())
    );

    connect(
        this,
        SIGNAL(racerListChanged()), 
        this, 
        SLOT(on_pb_calculateChances_clicked())
    );

    connect(
        this,
        SIGNAL(raceUpdated()), 
        this, 
        SLOT(on_raceUpdate())
    );

    connect(
        this,
        SIGNAL(raceUpdated()), 
        this, 
        SLOT(on_pb_calculateChances_clicked())
    );

    emit raceUpdated();

    setupModel();
}

MainWindow::~MainWindow()
{
    delete m_model;
    delete m_racersList;
    delete ui;
}





void MainWindow::on_moduleUpdate() 
{
    m_model->setStringList(*m_racersList);
}

void MainWindow::on_raceUpdate() 
{
    ui->lb_racInfo->setText(m_race.toString());
    ui->lb_chanceToSurvive->setText(QString::number(m_chance) + tr("%"));
}

void MainWindow::on_pb_addRacer_clicked()
{
    int key = Racer::getCountOfRacers() + 1;

    m_racersList->push_back(QString::number(key));
    m_racersMap.insert(key, Racer());

    emit racerListChanged();
}


void MainWindow::on_pb_removeRacer_clicked()
{
    auto selected = ui->lv_racersList->currentIndex();

    ui->lv_racersList->setCurrentIndex(QModelIndex());

    m_racersList->removeOne(selected.data().toString());

    emit racerListChanged();
}


void MainWindow::on_pb_calculateChances_clicked()
{
    float chance = 1.0;
    int deadCorners = 0;
    int carsWithWaterproof = 0;
    float chanceToSurviveOnCorner = 1.0 - ( 1.0 / m_racersList->count() );

    for (const auto c : m_racersMap)
    {
        carsWithWaterproof += c.getState() ? 1 : 0;
    }

    for (const auto c : m_race.getEvents())
    {
        deadCorners += c == eDeadlyEventType::DEADLYCHALLENGE ? 1 : 0;
    }

    float chanceToSurviveOnLake = static_cast<float>(carsWithWaterproof) / m_racersList->count();

    chance *= std::pow(chanceToSurviveOnCorner, static_cast<float>(deadCorners)) * chanceToSurviveOnLake;

    ui->lb_chanceToSurvive->setText(QString::number(chance) + tr("%"));
}


void MainWindow::on_lv_racersList_clicked(const QModelIndex &index)
{
    int key = index.data().toInt();
    
    qDebug() << m_racersMap.contains(key);

    auto const car = m_racersMap[key];

    ui->lb_carInfo->setText(car.toString());

    qDebug() << m_racersMap.count();
}


void MainWindow::on_pb_rerollRace_clicked()
{
    m_race = Race();

    emit raceUpdated();
}
