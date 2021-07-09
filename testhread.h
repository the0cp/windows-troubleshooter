#ifndef TESTHREAD_H
#define TESTHREAD_H

#include <QObject>
#include <QProcess>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QFile>

#include <unistd.h>
#include <direct.h>

#include "ui_systest.h"

class tesThread : public QObject
{
    Q_OBJECT
public:
    explicit tesThread(QObject *parent = nullptr);

    bool stopFlag = false;

    void testNetwork(QString DIRPATH);

    void testGeneral(QString DIRPATH);

    void testGen_soft(QString DIRPATH);

    void createProcess(QString CMD);

    QString getDir();
signals:
    void threadFinished();

public slots:
    void setFlag(bool flag = false);

    void starTest();

};

#endif // TESTHREAD_H
