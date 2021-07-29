#include "testhread.h"

tesThread::tesThread(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(sendComInfo(QString)), this, SLOT(saveComInfo(QString)));
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
        winInfo(DIRPATH);
    }

    if((Qt::CheckState)settings.value("101").toUInt() == Qt::Checked)
    {
        testGen_soft(DIRPATH);
    }

    if((Qt::CheckState)settings.value("110").toUInt() == Qt::Checked)
    {
        testGen_hard(DIRPATH);
    }

    if((Qt::CheckState)settings.value("111").toUInt() == Qt::Checked)
    {
        readCom();
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
        foreach(QString regItem , regGroups)
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

void tesThread::testGen_hard(QString DIRPATH)
{
    QFile file(DIRPATH + "\\General\\Hardware.txt");
    createProcess(gpu());
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << "[Local Host]" << endl << localHostName() << endl << endl;
        stream << "[CPU]" << endl << cpu() << endl << endl;
        //stream << "[Video Card(GPU)]" << endl;

        //stream << endl << endl;
        stream << "[Disk]" << endl << disk() << endl << endl;
        stream << "[Memory(RAM)]" << endl << ram() << endl << endl;
        //stream << "[Monitor/Screen]" << endl << screen() << endl << endl;
    }
    file.close();

}

void tesThread::winInfo(QString DIRPATH)
{
    QFile file(DIRPATH + "\\General\\Windows Info.txt");

    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << "Windows Version: " << QSysInfo::WindowsVersion << endl;
        stream << "Build Abi: " << QSysInfo::buildAbi() << endl;
        stream << "Build CPU Architecture: " << QSysInfo::buildCpuArchitecture() << endl;
        stream << "Current CPU Architecture: " << QSysInfo::currentCpuArchitecture() << endl;
        stream << "Kernel Type: " << QSysInfo::kernelType() << endl;
        stream << "Kernel Version: " << QSysInfo::kernelVersion() << endl;
        stream << "Machine Hostname: " << QSysInfo::machineHostName() << endl;
        stream << "Pretty Product Name: " << QSysInfo::prettyProductName() << endl;
        stream << "Product Type: " << QSysInfo::productType() << endl;
        stream << "Product Version: " << QSysInfo::productVersion() << endl;
    }
    file.close();
}

quint64 tesThread::getDiskSpace(QString iDriver, bool flag)
{
    LPCWSTR strDriver=(LPCWSTR)iDriver.utf16();
    ULARGE_INTEGER freeDiskSpaceAvailable, totalDiskSpace, totalFreeDiskSpace;

    GetDiskFreeSpaceEx( strDriver, &freeDiskSpaceAvailable, &totalDiskSpace, &totalFreeDiskSpace) ;
    if(flag)
    {
        return (quint64) totalDiskSpace.QuadPart/MB;
    }
    else
    {
        return (quint64) totalFreeDiskSpace.QuadPart/MB;
    }
}


QStringList tesThread::getDiskName()
{
    QFileInfoList list = QDir::drives();
    QStringList diskNameList(NULL);

    for (int i=0; i<list.count(); i++)
    {

        QString str = list.at(i).absoluteDir().absolutePath();
        diskNameList.append(str);
    }
    return diskNameList;
}

const QString tesThread::localHostName()
{
    QString machineName = QHostInfo::localHostName();
    return machineName;
}


const QString tesThread::mac()
{
    QString strMac;

        QList<QNetworkInterface> netList = QNetworkInterface::allInterfaces();
        foreach(QNetworkInterface item, netList)
        {
            if((QNetworkInterface::IsUp & item.flags()) && (QNetworkInterface::IsRunning & item.flags()))
            {
                if(strMac.isEmpty() || strMac < item.hardwareAddress())
                {
                    strMac = item.hardwareAddress();
                }
            }
        }
        return strMac;
}

const QString tesThread::cpu()
{
    QSettings *CPU = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",QSettings::NativeFormat);
    QString m_cpuDescribe = CPU -> value("ProcessorNameString").toString();
    delete CPU;

    return m_cpuDescribe;
}

const QString tesThread::gpu()
{
    /*
    QString dcard;
    QSettings *DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\services\\nvlddmkm\\Device0",QSettings::NativeFormat);
    QString type = DCard->value("Device Description").toString();
    delete DCard;

    QString dType = type;
    dType.trimmed();
    if(!dType.isEmpty())
        dcard = dType;

    DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\igfx\\Device0",QSettings::NativeFormat);
    type = DCard->value("Device Description").toString();
    delete DCard;

    dType = type;
    dType.trimmed();
    if(!dType.isEmpty())
        dcard = dcard + "\n" +dType;

    DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\amdkmdap\\Device0",QSettings::NativeFormat);
    type = DCard->value("Device Description").toString();
    delete DCard;

    dType = type;
    dType.trimmed();
    if(!dType.isEmpty())
        dcard = dcard + "\n" +dType;

    dcard.trimmed();
    return dcard;
    */
   QString qgpuRes = getDir() + "\\General";
   QString wmicCmd = "/c wmic path Win32_VideoController get /value >> " +
                    qgpuRes +
                    "\\Hardware_GPU.txt";
   return wmicCmd;

}

const QString tesThread::ram()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    int m_totalMem = statex.ullTotalPhys  * 1.0/ GB;
    double m_freeMem = statex.ullAvailPhys * 1.0 / GB;

    QString m_memDescribe = QString("Free %1 GB / Total %2 GB" ).
            arg(QString::asprintf("%.2f", m_freeMem)).arg(QString::asprintf("%.2f", m_totalMem));

    return m_memDescribe;

}

const QString tesThread::screen()
{
    QString m_screenDescribe = "";
    QList<QSize> screenSizeList;
    QList <int> screenCountList;

    for(int i=0; i<QApplication::desktop() -> screenCount(); i++)
    {
            QRect screenRect = QApplication::desktop() -> screenGeometry(i);
            QSize size(screenRect.width(), screenRect.height());

            bool bExist = false;
            for(int j=0; j<screenSizeList.length(); j++)
            {
                QSize existSize = screenSizeList.at(j);
                if(size == existSize)
                {
                    screenCountList[j]++;
                    bExist = true;
                    break;
                }
            }

            if(!bExist)
            {
                screenSizeList.append(size);
                screenCountList.append(1);
            }
        }

        QSize m_maxScreenSize = screenSizeList.at(0);
        for(int i=0; i<screenSizeList.length(); i++)
        {
            int width = screenSizeList.at(i).width();
            int height = screenSizeList.at(i).height();

            if(width > m_maxScreenSize.width() && height > m_maxScreenSize.height())
                m_maxScreenSize = screenSizeList.at(i);

            m_screenDescribe += QString ("(%1pixel x %2pixel) x %3个").arg(width).arg(height).arg(screenCountList.at(i));
            if(i!= screenSizeList.length()-1)
                m_screenDescribe += ", ";
        }

        return m_screenDescribe;
}

const QString tesThread::disk()
{
    QString res;
    QString ress;
    QStringList diskList = getDiskName();

    foreach(QString str, diskList)
    {
        if (str.isEmpty())
        {
            continue;
        }
        quint64 totalDiskSpace = getDiskSpace(str, true);
        quint64 freeDiskSpace = getDiskSpace(str, false);

        res += ("Flag: " + str + "\n" + "[Total:" + tr("%1").arg(totalDiskSpace) + "MB]" + "\n" + "[Free:" + tr("%1").arg(freeDiskSpace) + "MB]\n");

    }
    return res;
}

QString tesThread::getDir()
{
    QString qconfigPath = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings *config = new QSettings(qconfigPath, QSettings::IniFormat);
    QString qresDir = config -> value("settings/output").toString() + "/Result";

    qresDir.replace("/", "\\");
    return qresDir;
}

void tesThread::readCom()
{
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &serialport, list)
    {
        emit sendComInfo("Port Name: " + serialport.portName() +
                         "\nSerial Number: " + serialport.serialNumber() +
                         "\nDescription: " + serialport.description() +
                         "\nManufacturer: " + serialport.manufacturer() +
                         "\nSystem Location: " + serialport.systemLocation()
                         );

    }
}

void tesThread::saveComInfo(QString COM)
{
    QFile file(getDir() + "\\General\\Serial Comm.txt");

    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << COM;
    }
    file.close();
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
}
