#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once



#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <QDebug>
#include "race.h"
#include "racer.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    float m_chance = 0.0;

    Race m_race; 
    QStringList *m_racersList = new QStringList();
    QMap<int, Racer> m_racersMap;
    QStringListModel *m_model = new QStringListModel();

private:
    void setupModel();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void raceUpdated();
    void racerListChanged();

private slots:
    void on_moduleUpdate();
    void on_raceUpdate();
    void on_pb_addRacer_clicked();
    void on_pb_removeRacer_clicked();
    void on_pb_calculateChances_clicked();
    void on_lv_racersList_clicked(const QModelIndex &index);
    void on_pb_rerollRace_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
