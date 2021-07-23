#ifndef TESTHREAD_H
#define TESTHREAD_H

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

#include <unistd.h>
#include <direct.h>
#include <Windows.h>

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

    quint64 getDiskSpace(QString iDriver, bool flag);

    QStringList getDiskName();

    const QString localHostName();

    const QString mac();

    const QString cpu();

    const QString gpu();

    const QString ram();

    const QString screen();

    const QString disk();



    void createProcess(QString CMD);

    QString getDir();
signals:
    void threadFinished();

public slots:
    void setFlag(bool flag = false);

    void starTest();

};

#endif // TESTHREAD_H
