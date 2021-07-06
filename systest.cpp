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
    connect(ui -> selectCmd, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(treeItemChanged(QTreeWidgetItem *, int)));
}

sysTest::~sysTest()
{
    delete ui;
}

void sysTest::initTree()
{
    QString qconfigPath = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings *config = new QSettings(qconfigPath, QSettings::IniFormat);
    QSettings settings("Theodore Cooper", "Theo's System Test Tool");

    QTreeWidgetItem *rootNetwork = new QTreeWidgetItem(ui -> selectCmd);
    rootNetwork -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt:: ItemIsSelectable);
    rootNetwork -> setText(0, "Network");
    rootNetwork -> setText(1, "Test Network");

        QTreeWidgetItem *childPing = new QTreeWidgetItem(rootNetwork);
        childPing -> setText(0, "PING");
        childPing -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt:: ItemIsSelectable);


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


            QTreeWidgetItem *childNetstat_r = new QTreeWidgetItem(childNetstat);
            childNetstat_r -> setText(0, "-r");
            childNetstat_r -> setText(1, "IP routing table");

            QTreeWidgetItem *childNetstat_n = new QTreeWidgetItem(childNetstat);
            childNetstat_n -> setText(0, "-n");
            childNetstat_n -> setText(1, "active TCP connections");

            QTreeWidgetItem *childNetstat_a = new QTreeWidgetItem(childNetstat);
            childNetstat_a -> setText(0, "-a");
            childNetstat_a -> setText(1, "all active TCP connections & TCP/UDP ports on which the computer is listening");




    QTreeWidgetItem *rootPCInfo = new QTreeWidgetItem(ui -> selectCmd);
    rootPCInfo -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt:: ItemIsSelectable);
    rootPCInfo -> setText(0, "General");
    rootPCInfo -> setText(1, "Get this Windows PC's informations.");

        QTreeWidgetItem *childBasic = new QTreeWidgetItem(rootPCInfo);
        childBasic -> setText(0, "Basic");
        childBasic -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt:: ItemIsSelectable);

            QTreeWidgetItem *childBasic_win = new QTreeWidgetItem(childBasic);
            childBasic_win -> setText(0, "Windows' info");
            childBasic_win -> setText(1, "Windows' basic informations.");

            QTreeWidgetItem *childBasic_software = new QTreeWidgetItem(childBasic);
            childBasic_software -> setText(0, "Software");
            childBasic_software -> setText(1, "Check installed software.");

        QTreeWidgetItem *childAdvan = new QTreeWidgetItem(rootPCInfo);
        childAdvan -> setText(0, "Advanced");
        childAdvan -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt:: ItemIsSelectable);

            QTreeWidgetItem *childAdvan_hardware = new QTreeWidgetItem(childAdvan);
            childAdvan_hardware -> setText(0, "Hardware");
            childAdvan_hardware -> setText(1, "Check your hardwares.");


    ui -> selectCmd -> expandAll();

        if(config -> value("settings/UseDefaultTestItems") == 1)
        {
            config -> setValue("settings/UseDefaultTestItems", 0);
            rootNetwork -> setCheckState(0, Qt::Checked);
                childPing -> setCheckState(0, Qt::Checked);
                    childPing_l -> setCheckState(0, Qt::Checked);
                    childPing_g -> setCheckState(0, Qt::Checked);
                    childPing_b -> setCheckState(0, Qt::Checked);
                childNetstat -> setCheckState(0, Qt::PartiallyChecked);
                    childNetstat_r -> setCheckState(0, Qt::Checked);
                    childNetstat_n -> setCheckState(0, Qt::Checked);
                    childNetstat_a -> setCheckState(0, Qt::Unchecked);
            rootPCInfo -> setCheckState(0, Qt::Checked);
                childBasic -> setCheckState(0, Qt::Checked);
                    childBasic_win -> setCheckState(0, Qt::Checked);
                    childBasic_software -> setCheckState(0, Qt::Checked);
                childAdvan -> setCheckState(0, Qt::Checked);
                    childAdvan_hardware -> setCheckState(0, Qt::Checked);
        }
        else
        {
            qDebug()<<(Qt::CheckState)settings.value("Network").toUInt()<<endl;
            childPing -> setCheckState(0, (Qt::CheckState)settings.value("00").toUInt());
                childPing_l -> setCheckState(0, (Qt::CheckState)settings.value("000").toUInt());
                childPing_g -> setCheckState(0, (Qt::CheckState)settings.value("001").toUInt());
                childPing_b -> setCheckState(0, (Qt::CheckState)settings.value("002").toUInt());
            childNetstat -> setCheckState(0, (Qt::CheckState)settings.value("01").toUInt());
                childNetstat_r -> setCheckState(0, (Qt::CheckState)settings.value("010").toUInt());
                childNetstat_n -> setCheckState(0, (Qt::CheckState)settings.value("011").toUInt());
                childNetstat_a -> setCheckState(0, (Qt::CheckState)settings.value("012").toUInt());

            childBasic -> setCheckState(0, (Qt::CheckState)settings.value("10").toUInt());
                childBasic_win -> setCheckState(0, (Qt::CheckState)settings.value("100").toUInt());
                childBasic_software -> setCheckState(0, (Qt::CheckState)settings.value("101").toUInt());
            childAdvan -> setCheckState(0, (Qt::CheckState)settings.value("11").toUInt());
                childAdvan_hardware -> setCheckState(0, (Qt::CheckState)settings.value("110").toUInt());

        }
}

void sysTest::updateParentItem(QTreeWidgetItem* item)
{
    QTreeWidgetItem *parent = item -> parent();
    QTreeWidgetItem *root = parent -> parent();
    QSettings settings("Theodore Cooper", "Theo's System Test Tool");
    int selectedCount = 0;
    int childCount = parent -> childCount();
    int rootrootNum = ui -> selectCmd -> indexOfTopLevelItem(root);
    int rootNum = parent -> parent() -> indexOfChild(parent);

    if(parent == NULL)
    {
        return ;
    }

    for(int i = 0; i < childCount; i++)
    {
        QString nodeNum = QString::number(rootrootNum) + QString::number(rootNum) + QString::number(i);

        QTreeWidgetItem *childItem = parent->child(i);

        if(childItem -> checkState(0) == Qt::Checked || childItem->checkState(0) == Qt::PartiallyChecked)
        {
            settings.setValue(nodeNum, Qt::Checked);
            selectedCount++;
        }
        else
        {
            settings.setValue(nodeNum, Qt::Unchecked);
        }
    }

    if(selectedCount <= 0)
    {
        parent->setCheckState(0, Qt::Unchecked);
        settings.setValue(QString::number(rootrootNum) + QString::number(rootNum), Qt::Unchecked);
    }

    else if(selectedCount > 0 && selectedCount < childCount)
    {
        parent->setCheckState(0, Qt::PartiallyChecked);
        settings.setValue(QString::number(rootrootNum) + QString::number(rootNum), Qt::PartiallyChecked);
    }

    else if(selectedCount == childCount)
    {
        parent->setCheckState(0, Qt::Checked);
        settings.setValue(QString::number(rootrootNum) + QString::number(rootNum), Qt::Checked);
    }
}

void sysTest::treeItemChanged(QTreeWidgetItem* item, int column)
{
    if( column!=0 )
    {
        return;
    }

    if(Qt::Checked == item -> checkState(0))
    {
        // QTreeWidgetItem* parent = item->parent();
        int count = item -> childCount();
        if(count > 0)
        {
            for(int i = 0; i < count; i++)
            {
                item->child(i) -> setCheckState(0,Qt::Checked);
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
            for(int i = 0; i < count; i++)
            {
                item->child(i) -> setCheckState(0,Qt::Unchecked);
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

void sysTest::closeEvent(QCloseEvent *event)
{
    QSettings settings("Theodore Cooper", "Theo's System Test Tool");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

