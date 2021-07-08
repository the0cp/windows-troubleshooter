#include "testhread.h"

tesThread::tesThread(QObject *parent) : QObject(parent)
{

}

void tesThread::setFlag(bool flag)
{
    stopFlag = flag;
}

void tesThread::createProcess(QString CMD)
{

    /*
    std::wstring wlpstrstd = CMD.toStdWString();
    LPCWSTR lCMD = wlpstrstd.c_str();

    PROCESS_INFORMATION  ProcessInfo;
    STARTUPINFO  StartupInfo;
    ZeroMemory(&StartupInfo,  sizeof(StartupInfo));

    //Another way to hide the window:

    StartupInfo.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = SW_HIDE;


    StartupInfo.cb  =  sizeof(StartupInfo);

    if(CreateProcess(NULL, (LPWSTR)lCMD, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
    {
        WaitForSingleObject(ProcessInfo.hProcess,INFINITE); //That's why I don't use WinExec();
        CloseHandle(ProcessInfo.hThread);
        CloseHandle(ProcessInfo.hProcess);
    }   //Hide the window -- that's why I don't use system();
    */

    QProcess p(0);
        p.start("cmd", QStringList()<<CMD);
        //p.waitForStarted();
        p.waitForFinished();
}

void tesThread::testNetwork(QString DIRPATH)
{
    //test network

    QSettings settings("Theodore Cooper", "Theo's System Test Tool");

    QString qnetRes = DIRPATH + "\\Network";

    /**********************
     * ping Test:
     * ping localhost
     * ping google
     * ping bing
     **********************/

    QByteArray ba = qnetRes.toLatin1();
    char *netRes = ba.data();
    mkdir(netRes);

    QString qping_localhost = " /c echo [PING LOCALHOST] >> " +
                             qnetRes + "\\ping.txt" +
                             " && ping 127.0.0.1 >> " +
                             qnetRes +
                             "\\ping.txt && echo: >> " +
                             qnetRes +
                             "\\ping.txt";

    QString qping_google = " /c echo [PING GOOGLE] >> " +
                             qnetRes + "\\ping.txt" +
                             " && ping www.google.com >> " +
                             qnetRes +
                             "\\ping.txt && echo: >> " +
                             qnetRes +
                             "\\ping.txt";

    QString qping_bing = " /c echo [PING BING] >> " +
                             qnetRes + "\\ping.txt" +
                             " && ping www.bing.com >> " +
                             qnetRes +
                             "\\ping.txt && echo: >> " +
                             qnetRes +
                             "\\ping.txt";

    if((Qt::CheckState)settings.value("000").toUInt() == Qt::Checked)
    {
        createProcess(qping_localhost);
    }

    if((Qt::CheckState)settings.value("001").toUInt() == Qt::Checked)
    {
        createProcess(qping_google);
    }

    if((Qt::CheckState)settings.value("002").toUInt() == Qt::Checked)
    {
        createProcess(qping_bing);
    }




    /**********************
     * netstat Test
     * netstat -r
     * netstat -n
     * netstat -a
     **********************/

    QString qnetstat_r = "/c netstat -r >> " +
                       qnetRes+ "\\netstat.txt";
    QString qnetstat_n = "/c netstat -n >> " +
                       qnetRes+ "\\netstat.txt";
    QString qnetstat_a = "/c netstat -a >> " +
                       qnetRes+ "\\netstat.txt";

    if((Qt::CheckState)settings.value("010").toUInt() == Qt::Checked)
    {
        createProcess(qnetstat_r);
        //Displays the contents of the IP routing table.
    }

    if((Qt::CheckState)settings.value("011").toUInt() == Qt::Checked)
    {
        createProcess(qnetstat_n);
        //Displays active TCP connections.
    }

    if((Qt::CheckState)settings.value("012").toUInt() == Qt::Checked)
    {
        createProcess(qnetstat_a);
        //Displays all active TCP connections and the TCP and UDP ports on which the computer is listening.
    }



}

void tesThread::testGeneral(QString DIRPATH)
{
    QSettings settings("Theodore Cooper", "Theo's System Test Tool");

    QString qgenRes = DIRPATH + "\\General";

    QByteArray ba = qgenRes.toLatin1();
    char *genRes = ba.data();
    mkdir(genRes);

    if((Qt::CheckState)settings.value("100").toUInt() == Qt::Checked)
    {
        //win
    }

    if((Qt::CheckState)settings.value("101").toUInt() == Qt::Checked)
    {
        testGen_soft(DIRPATH);
    }

    if((Qt::CheckState)settings.value("110").toUInt() == Qt::Checked)
    {
        //hardware
    }
}

void tesThread::testGen_soft(QString DIRPATH)
{

    QFile file(DIRPATH + "\\General\\Software.txt");

    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        QString regStr = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\";
        QSettings settings(regStr, QSettings::NativeFormat);
        QStringList regGroups = settings.childGroups();
        foreach (QString regItem , regGroups)
        {
            settings.beginGroup(regItem);
            QString displayName = settings.value("DisplayName").toString();
            QString uninstallString = settings.value("UninstallString").toString();
            if(!displayName.isEmpty())
            {
                //qDebug() << "[" << __FUNCTION__ <<__LINE__ << "]:" << displayName << uninstallString;
                stream << "[" << __FUNCTION__ <<__LINE__ << "]:" << displayName << uninstallString << "\n";
            }
            settings.endGroup();

        }
        file.close();
    }
}

QString tesThread::getDir()
{
    QString qconfigPath = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings *config = new QSettings(qconfigPath, QSettings::IniFormat);
    QString qresDir = config -> value("settings/output").toString() + "/Result";

    qresDir.replace("/", "\\");
    return qresDir;
}

void tesThread::starTest()
{
    //start testing
    QString qresDir = getDir();
    QByteArray ba = qresDir.toLatin1();
    char *resDir = ba.data();
    QString qrmDir = " /c rd /s /q " + qresDir;
    if(access(resDir, 0) == 0)
    {
        createProcess(qrmDir);
    }
    mkdir(resDir);
    testGeneral(qresDir);
    testNetwork(qresDir);
    emit threadFinished();
    qDebug()<<"emitted"<<endl;
}
