#ifndef TESTHREAD_H
#define TESTHREAD_H

#include <QObject>
#include <QProcess>
#include <QSettings>
#include <QCoreApplication>

#include <unistd.h>
#include <direct.h>

class tesThread : public QObject
{
    Q_OBJECT
public:
    explicit tesThread(QObject *parent = nullptr);

    bool stopFlag = false;

    void testNetwork(QString CMD);

    void createProcess(QString CMD);

    QString getDir();
signals:

public slots:
    void setFlag(bool flag = false);

    void starTest();

};

#endif // TESTHREAD_H
