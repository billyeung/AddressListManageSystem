#include "mainwindow.h"
#include "ui_mainwindow.h"

QLabel *stalabel;
int k;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    Inittable(ui->tableWidget);
    Inittable(ui->tableWidget_2);
    stalabel = new QLabel(this);
    ui->statusBar->addWidget(stalabel);
    stalabel->setText("Welcome!");
    QSettings settings("config.ini", QSettings::IniFormat);//读取配置信息
    QString filepath = settings.value("Path/filepath").toString();
    if(adlist.Readfile(filepath)) {//成功打开文件
        Settable(0);
        ui->comboBox->setEnabled(true);
        ui->apply->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->searchline->setEnabled(true);
        ui->actionExport->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Getfile(QString qstr) //打开文档
{
    if(!adlist.Readfile(qstr)){
        errdlg = new Errdlg(this);
        connect(this,SIGNAL(error(int)),errdlg,SLOT(stack(int)));
        emit error(3);
        errdlg->exec();
        on_actionImport_triggered();
        return;
    }
    Settable(0);
    ui->comboBox->setEnabled(true);
    ui->apply->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
    ui->searchline->setEnabled(true);
    ui->actionExport->setEnabled(true);
    ui->statusBar->showMessage("Imported successfully!",2000);
}

string strtoemp(string str) //使空字符串和"no"互相转换
{
    if(str=="no") str = "\0";
    return str;
}

void MainWindow::Inittable(QTableWidget *table)//初始化表格
{
    connect(table->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(slot_sortByColumn(int, QTableWidget*)));
    table->setRowCount(0);
    table->setColumnCount(4);
    table->setColumnWidth(0,100);
    table->setColumnWidth(1,160);
    table->setColumnWidth(2,169);
    table->setColumnWidth(3,80);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QStringList header;
    header << "Name" << "Phone number"<<"E-mail"<<"Group";
    table->setHorizontalHeaderLabels(header);
}

void MainWindow::slot_sortByColumn(int idx, QTableWidget *table)//使表格内容排序
{
    static int i = 0;
    if(i){
        table->sortByColumn(idx,Qt::AscendingOrder);
        i = 0;
    }
    else{
        table->sortByColumn(idx,Qt::DescendingOrder);
        i = 1;
    }
}

void MainWindow::Printcontact(QTableWidget *table, PNode lastptr, char *k1)//打印联系人信息
{
    QString group;
    table->insertRow(0);
    QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::fromStdString(strtoemp(lastptr->name)));
    newItem1->setTextAlignment(0x0002);
    table->setItem(0, 0, newItem1);
    QTableWidgetItem *newItem2 = new QTableWidgetItem(QString::fromStdString(strtoemp(lastptr->pnum)));
    newItem2->setTextAlignment(0x0002);
    table->setItem(0, 1, newItem2);
    QTableWidgetItem *newItem3 = new QTableWidgetItem(QString::fromStdString(strtoemp(lastptr->email)));
    newItem3->setTextAlignment(0x0002);
    table->setItem(0, 2, newItem3);
    if(lastptr->group == "de") group = "Default";
    else if(lastptr->group == "fa") group = "Family";
    else if(lastptr->group == "fr") group = "Friend";
    else if(lastptr->group == "co") group = "Colleague";
    QTableWidgetItem *newItem4 = new QTableWidgetItem(group);
    newItem4->setTextAlignment(0x0005);
    table->setItem(0, 3, newItem4);
    QTableWidgetItem *newItem5 = new QTableWidgetItem(k1);
    table->setItem(0, 4, newItem5);
}

void MainWindow::Settable(int idx)//设置表格内容
{
    string group;
    int k = 0;
    char k1[5];
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,160);
    ui->tableWidget->setColumnWidth(2,169);
    ui->tableWidget->setColumnWidth(3,80);
    ui->tableWidget->setColumnWidth(4,0);
    PNode lastptr = adlist.Getlist()->head->next;
    while(lastptr){
        switch (idx) {
        case 0:
            group = lastptr->group;
            break;
        case 1:
            group = "fa";
            break;
        case 2:
            group = "fr";
            break;
        case 3:
            group = "co";
            break;
        case 4:
            group = "de";
            break;
        }
        if(lastptr->group == group)
        {
            itoa(k, k1, 10);
            Printcontact(ui->tableWidget, lastptr, k1);
        }
        lastptr=lastptr->next;
        k++;
    }
    ui->tableWidget->show();
    char amount[25];
    itoa(adlist.Getlist()->size,amount,10);
    strcat(amount," contacts in total.");
    stalabel->setText(amount);
}

void MainWindow::Searchtable(int idx, QString qstr)//设置查询表格内容
{
    int results = 0;
    int k = 0;
    char k1[5];
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(5);
    ui->tableWidget_2->setColumnWidth(0,100);
    ui->tableWidget_2->setColumnWidth(1,160);
    ui->tableWidget_2->setColumnWidth(2,169);
    ui->tableWidget_2->setColumnWidth(3,80);
    ui->tableWidget_2->setColumnWidth(4,0);
    PNode lastptr = adlist.Getlist()->head->next;
    while(lastptr){
        switch(idx){
        case 0:
            if(QString::fromStdString(lastptr->name).indexOf(qstr)>=0) {
                itoa(k, k1, 10);
                Printcontact(ui->tableWidget_2, lastptr, k1);
                results++;
            }
            break;
        case 1:
            if((qstr.isEmpty()&&lastptr->pnum=="no")||(!qstr.isEmpty()&&QString::fromStdString(lastptr->pnum).indexOf(qstr)>=0)) {
                itoa(k, k1, 10);
                Printcontact(ui->tableWidget_2, lastptr, k1);
                results++;
            }
            break;
        case 2:
            if((qstr.isEmpty()&&lastptr->qnum=="no")||(!qstr.isEmpty()&&QString::fromStdString(lastptr->qnum).indexOf(qstr)>=0)) {
                itoa(k, k1, 10);
                Printcontact(ui->tableWidget_2, lastptr, k1);
                results++;
            }
            break;
        case 3:
            if((qstr.isEmpty()&&lastptr->email=="no")||(!qstr.isEmpty()&&QString::fromStdString(lastptr->email).indexOf(qstr)>=0)) {
                itoa(k, k1, 10);
                Printcontact(ui->tableWidget_2, lastptr, k1);
                results++;
            }
            break;
        }
        lastptr=lastptr->next;
        k++;
    }
    ui->tableWidget_2->show();
    char result[25];
    itoa(results,result,10);
    strcat(result," results found.");
    stalabel->setText(result);
}

void MainWindow::Showdetail(int k)//显示详细信息
{
    QString group;
    PNode lastptr = adlist.Getlist()->head->next;
    for(int i=0; i<k; i++) lastptr = lastptr->next;
    ui->textBrowser->setText(QString::fromStdString(strtoemp(lastptr->name)));
    ui->textBrowser_2->setText(QString::fromStdString(strtoemp(lastptr->pnum)));
    ui->textBrowser_3->setText(QString::fromStdString(strtoemp(lastptr->qnum)));
    ui->textBrowser_4->setText(QString::fromStdString(strtoemp(lastptr->email)));
    ui->textBrowser_5->setText(QString::fromStdString(strtoemp(lastptr->address)));
    if(lastptr->group == "de") group = "Default";
    else if(lastptr->group == "fa") group = "Family";
    else if(lastptr->group == "fr") group = "Friend";
    else if(lastptr->group == "co") group = "Colleague";
    ui->textBrowser_6->setText(group);
}

void MainWindow::Exportfile(QString qstr)//导出通讯录
{
    adlist.Exportfile(qstr);
    ui->statusBar->showMessage("Exported successfully!",2000);
}

void MainWindow::Insertcontact(QString qname,QString qpnum,QString qqnum,QString qemail,QString qaddress,QString qgroup)//新建联系人
{
    adlist.Insert(qname.toStdString(),qpnum.toStdString(),qqnum.toStdString(),qemail.toStdString(),qaddress.toStdString(),qgroup.toStdString());
    if(ui->comboBox->currentIndex() == 0) Settable(0);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->setEnabled(true);
    ui->apply->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
    ui->searchline->setEnabled(true);
    ui->actionExport->setEnabled(true);
    if(adlist.Getpath() != "") ui->actionSave->setEnabled(true);
    ui->statusBar->showMessage("Added successfully!",2000);
}

void MainWindow::Deletecontact()//删除联系人
{
    adlist.Delete(k);
    ui->actionSave->setEnabled(true);
    if(adlist.Getlist()->head->next == NULL){
        ui->actionModify->setEnabled(false);
        ui->actionDelete->setEnabled(false);
    }
    ui->statusBar->showMessage("Deleted successfully!",2000);
    Settable(ui->comboBox->currentIndex());
}

void MainWindow::Modifycontact(QString qname,QString qpnum,QString qqnum,QString qemail,QString qaddress,QString qgroup)//编辑联系人
{
    adlist.Modify(k,qname.toStdString(),qpnum.toStdString(),qqnum.toStdString(),qemail.toStdString(),qaddress.toStdString(),qgroup.toStdString());
    if(ui->comboBox->currentIndex() == 0) Settable(0);
    ui->comboBox->setCurrentIndex(0);
    ui->actionSave->setEnabled(true);
    ui->statusBar->showMessage("Modified successfully!",2000);
}

void MainWindow::on_actionExport_triggered()
{
    efdlg = new QFileDialog(this);
    efdlg->setAcceptMode(QFileDialog::AcceptSave);
    efdlg->setWindowTitle(tr("Export File"));
    efdlg->setNameFilter(tr("Text Documents(*.txt)"));
    if(efdlg->exec() == QDialog::Accepted) {
           QString path = efdlg->selectedFiles()[0];
           Exportfile(path);
    }
}

void MainWindow::on_actionSave_triggered()
{
    adlist.Savefile();
    ui->actionSave->setEnabled(false);
}

void MainWindow::on_actionNew_triggered()
{
    newcontact = new Newcontact(this);
    connect(newcontact,SIGNAL(sendData(QString,QString,QString,QString,QString,QString)),this,SLOT(Insertcontact(QString,QString,QString,QString,QString,QString)));
    newcontact->exec();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        Settable(0);
        break;
    case 1:
        Settable(1);
        break;
    case 2:
        Settable(2);
        break;
    case 3:
        Settable(3);
        break;
    case 4:
        Settable(4);
        break;
    }
}

void MainWindow::on_actionSearch_triggered(bool checked)
{
    if(checked == true) {
        ui->stackedWidget->setCurrentIndex(1);
        Inittable(ui->tableWidget_2);
    }
    else {
        ui->stackedWidget->setCurrentIndex(0);
        char amount[25];
        itoa(adlist.Getlist()->size,amount,10);
        strcat(amount," contacts in total.");
        stalabel->setText(amount);
    }

}

void MainWindow::on_apply_clicked()
{
    int idx = ui->comboBox_2->currentIndex();
    if(idx==0&&ui->searchline->text().isEmpty()){
        errdlg = new Errdlg(this);
        connect(this,SIGNAL(error(int)),errdlg,SLOT(stack(int)));
        emit error(2);
        errdlg->exec();
        return;
    }
    QString qstr = ui->searchline->text();
    Searchtable(idx, qstr);
}

void MainWindow::on_searchline_returnPressed()
{
    on_apply_clicked();
}

void MainWindow::on_actionDelete_triggered()
{
    deletedlg = new Deletedlg(this);
    connect(deletedlg,SIGNAL(apply()),this,SLOT(Deletecontact()));
    deletedlg->exec();
}

void MainWindow::on_actionAbout_triggered()
{
    abdlg = new Abdlg(this);
    abdlg->exec();
}

void MainWindow::on_actionHelp_triggered()
{
    helpdlg = new Helpdlg(this);
    helpdlg->exec();
}

void MainWindow::on_actionImport_triggered()
{
    fdlg = new QFileDialog(this);
    fdlg->setAcceptMode(QFileDialog::AcceptOpen);
    fdlg->setWindowTitle(tr("Import File"));
    fdlg->setNameFilter(tr("Text Documents(*.txt)"));
    if(fdlg->exec() == QDialog::Accepted) {
           QString path = fdlg->selectedFiles()[0];
           Getfile(path);
    }
}

void MainWindow::on_actionModify_triggered()
{
    modcontact = new Modcontact(this);
    connect(this,SIGNAL(condetails(QString, QString, QString, QString, QString, QString)),modcontact,SLOT(modcontact(QString, QString, QString, QString, QString, QString)));
    connect(modcontact,SIGNAL(sendData(QString, QString, QString, QString, QString, QString)),this,SLOT(Modifycontact(QString, QString, QString, QString, QString, QString)));
    emit condetails(ui->textBrowser->toPlainText(), ui->textBrowser_2->toPlainText(), ui->textBrowser_3->toPlainText(), ui->textBrowser_4->toPlainText(), ui->textBrowser_5->toPlainText(), ui->textBrowser_6->toPlainText());
    modcontact->exec();
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(focus == false){
        ui->actionDelete->setEnabled(false);
        ui->actionModify->setEnabled(false);
        ui->textBrowser->clear();
        ui->textBrowser_2->clear();
        ui->textBrowser_3->clear();
        ui->textBrowser_4->clear();
        ui->textBrowser_5->clear();
        ui->textBrowser_6->clear();
    }
    else{
        ui->actionDelete->setEnabled(true);
        ui->actionModify->setEnabled(true);
        QTableWidgetItem* item = ui->tableWidget->currentItem();
        int row = item->row();
        QString label = ui->tableWidget->item(row, 4)->text();
        char *k1;
        QByteArray ba=label.toLatin1();
        k1=ba.data();
        k = atoi(k1);
        Showdetail(k);
    }
}

void MainWindow::on_tableWidget_2_itemSelectionChanged()
{
    bool focus = ui->tableWidget_2->isItemSelected(ui->tableWidget_2->currentItem());
    if(focus == false){
        ui->actionDelete->setEnabled(false);
        ui->actionModify->setEnabled(false);
        ui->textBrowser->clear();
        ui->textBrowser_2->clear();
        ui->textBrowser_3->clear();
        ui->textBrowser_4->clear();
        ui->textBrowser_5->clear();
        ui->textBrowser_6->clear();
    }
    else{
        ui->actionDelete->setEnabled(true);
        ui->actionModify->setEnabled(true);
        QTableWidgetItem* item = ui->tableWidget_2->currentItem();
        int row = item->row();
        QString label = ui->tableWidget_2->item(row, 4)->text();
        char *k1;
        QByteArray ba=label.toLatin1();
        k1=ba.data();
        k = atoi(k1);
        Showdetail(k);
    }
}
