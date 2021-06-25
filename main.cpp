#include "systest.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "sysTest_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }
    QString qconfigPath = QCoreApplication::applicationDirPath() + "/config.ini";
    QByteArray ba = qconfigPath.toLatin1();
    char* configPath= ba.data();
    if(access(configPath, 0) == -1)
    {
        QSettings *config = new QSettings(qconfigPath, QSettings::IniFormat);
        config -> setValue("settings/output", -1);
    }

    sysTest w;
    w.show();
    return a.exec();
}
