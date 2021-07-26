#ifndef TESTHREAD_H
#define TESTHREAD_H

#include <unistd.h>
#include <direct.h>
#include <Windows.h>

#include <QObject>
#include <QProcess>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QFile>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopWidget>
#include <QFileInfoList>
#include <QDir>
#include <QList>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>



#include "ui_systest.h"

#define MB (1024*1024)
#define GB (1024*1024*1024)

class tesThread : public QObject
{
    Q_OBJECT
public:
    explicit tesThread(QObject *parent = nullptr);

    bool stopFlag = false;

    void testNetwork(QString DIRPATH);

    void testGeneral(QString DIRPATH);

    void testGen_soft(QString DIRPATH);

    void testGen_hard(QString DIRPATH);

    void winInfo(QString DIRPATH);

    void readCom();

    quint64 getDiskSpace(QString iDriver, bool flag);

    QStringList getDiskName();

    const QString localHostName();

    const QString mac();

    const QString cpu();

    const QString gpu();

    const QString ram();

    const QString screen();

    const QString disk();



    void createProcess(QString);

    QString getDir();
signals:
    void threadFinished();

    void sendComInfo(QString COM);

public slots:
    void setFlag(bool flag = false);

    void starTest();

    void saveComInfo(QString COM);

};

#endif // TESTHREAD_H
