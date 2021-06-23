#include "systest.h"
#include "ui_systest.h"

sysTest::sysTest(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sysTest)
{
    ui -> setupUi(this);
    ui -> outputDir -> setReadOnly(true);
    QString qconfigPath = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings *config = new QSettings(qconfigPath, QSettings::IniFormat);
    ui -> outputDir -> setText(config -> value("/settings/output").toString());
    newThread = new QThread;
    object = new tesThread;
    object -> moveToThread(newThread);

    connect(ui -> btn_start, SIGNAL(clicked()), object, SLOT(starTest()));
}

sysTest::~sysTest()
{
    delete ui;
}


void sysTest::on_browse_clicked()
{
    QString outputPath;
    outputPath = QFileDialog::getExistingDirectory(this, "Choose your output directory...",
                                                          "C:/",
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
    //output_path.replace("/", "\\");
    QString qconfigPath = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings *config = new QSettings(qconfigPath, QSettings::IniFormat);
    config -> setValue("settings/output", outputPath);
    ui -> outputDir -> setText(outputPath);
}


void sysTest::on_btn_start_clicked()
{
    qDebug()<<"start thread"<<endl;
    newThread -> start();
    object->setFlag(false);
}

