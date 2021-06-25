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

    if(config -> value("settings/output").toInt() == -1)
    {
        config -> setValue("settings/output", "C:/");
    }
    ui -> outputDir -> setText(config -> value("settings/output").toString());

    initTree();

    newThread = new QThread;
    object = new tesThread;
    object -> moveToThread(newThread);

    connect(ui -> btn_start, SIGNAL(clicked()), object, SLOT(starTest()));
    connect(ui -> selectCmd,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));}

sysTest::~sysTest()
{
    delete ui;
}

void sysTest::initTree()
{
    QTreeWidgetItem *rootNetwork = new QTreeWidgetItem(ui -> selectCmd);
    rootNetwork -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt:: ItemIsSelectable);
    rootNetwork -> setCheckState(0,Qt::Checked);
    rootNetwork -> setText(0, "Network");
    rootNetwork -> setText(1, "Test Network");

        QTreeWidgetItem *childPing = new QTreeWidgetItem(rootNetwork);
        childPing -> setText(0, "PING");
        childPing -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt:: ItemIsSelectable);
        childPing -> setCheckState(0, Qt::Checked);

            QTreeWidgetItem *childPing_l = new QTreeWidgetItem(childPing);
            childPing_l -> setText(0, "localhost");
            childPing_l -> setText(1, "ping localhost");

            QTreeWidgetItem *childPing_g = new QTreeWidgetItem(childPing);
            childPing_g -> setText(0, "Google");
            childPing_g -> setText(1, "ping Google's site (www.google.com)");

            QTreeWidgetItem *childPing_b = new QTreeWidgetItem(childPing);
            childPing_b -> setText(0, "Bing");
            childPing_b -> setText(1, "ping Bing's site (www.bing.com)");

        QTreeWidgetItem *childNetstat = new QTreeWidgetItem(rootNetwork);
        childNetstat -> setText(0, "NETSTAT");
        childNetstat -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt:: ItemIsSelectable);
        childNetstat -> setCheckState(0, Qt::Checked);

            QTreeWidgetItem *childNetstat_r = new QTreeWidgetItem(childNetstat);
            childNetstat_r -> setText(0, "-r");
            childNetstat_r -> setText(1, "IP routing table");

            QTreeWidgetItem *childNetstat_n = new QTreeWidgetItem(childNetstat);
            childNetstat_n -> setText(0, "-n");
            childNetstat_n -> setText(1, "active TCP connections");

            QTreeWidgetItem *childNetstat_a = new QTreeWidgetItem(childNetstat);
            childNetstat_a -> setText(0, "-a");
            childNetstat_a -> setText(1, "all active TCP connections & TCP/UDP ports on which the computer is listening");
}

void tesThread::updateParentItem(QTreeWidgetItem* item)
{
    QTreeWidgetItem *parent = item->parent();
    if(parent == NULL)
    {
        return ;
    }
    int selectedCount = 0;
    int childCount = parent->childCount();
    for(int i=0; i<childCount; i++)
    {
        QTreeWidgetItem* childItem = parent->child(i);
        if(childItem->checkState(0) == Qt::Checked)
        {
            selectedCount++;
        }
    }
    if(selectedCount <= 0)
    {
        parent->setCheckState(0,Qt::Unchecked);
    }
    else if(selectedCount>0 && selectedCount<childCount)
    {
        parent->setCheckState(0,Qt::PartiallyChecked);
    }
    else if(selectedCount == childCount)
    {
        parent->setCheckState(0,Qt::Checked);
    }
}

void tesThread::treeItemChanged(QTreeWidgetItem* item, int column)
{
    if(Qt::Checked == item->checkState(0))
    {
        int count = item->childCount();
        if(count >0)
        {
            for(int i=0; i<count; i++)
            {
                item->child(i)->setCheckState(0,Qt::Checked);
            }
        }
        else
        {
            updateParentItem(item);
        }
     }
    else if(Qt::Unchecked == item->checkState(0))
    {
        int count = item->childCount();
        if(count > 0)
        {
            for(int i=0; i<count; i++)
            {
                item->child(i)->setCheckState(0,Qt::Unchecked);
            }
        }
        else
        {
            updateParentItem(item);
        }
    }
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
    if(config -> value("settings/output").toInt() == -1)
    {
        config -> setValue("settings/output", "C:/");
    }
    config -> setValue("settings/output", outputPath);
    ui -> outputDir -> setText(outputPath);
}


void sysTest::on_btn_start_clicked()
{
    qDebug()<<"start thread"<<endl;
    newThread -> start();
    object->setFlag(false);
}

