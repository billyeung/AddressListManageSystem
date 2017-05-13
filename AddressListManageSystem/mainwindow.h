#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>
#include <fstream>
#include <string>
#include "abdlg.h"
#include "addrlist.h"
#include "helpdlg.h"
#include "newcontact.h"
#include "deletedlg.h"
#include "modcontact.h"
#include "qtablewidget.h"
#include "qfiledialog.h"
#include "errdlg.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionImport_triggered();
    void Getfile(QString);
    void Printcontact(QTableWidget*, PNode, char*);
    void Settable(int);
    void Searchtable(int,QString);
    void Inittable(QTableWidget *);
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
    void slot_sortByColumn(int, QTableWidget*);
    void Exportfile(QString);
    void Insertcontact(QString, QString, QString, QString, QString, QString);
    void Deletecontact();
    void Modifycontact(QString, QString, QString, QString, QString, QString);
    void Showdetail(int);
    void on_actionExport_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_comboBox_currentIndexChanged(int index);
    void on_actionSearch_triggered(bool checked);
    void on_apply_clicked();
    void on_searchline_returnPressed();
    void on_actionDelete_triggered();
    void on_actionModify_triggered();
    void on_tableWidget_itemSelectionChanged();
    void on_tableWidget_2_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    Abdlg *abdlg;
    Helpdlg *helpdlg;
    Newcontact *newcontact;
    Modcontact *modcontact;
    Deletedlg *deletedlg;
    QFileDialog *fdlg;
    QFileDialog *efdlg;
    Errdlg *errdlg;

signals:
    void condetails(QString, QString, QString, QString, QString, QString);
    void error(int);
};

#endif // MAINWINDOW_H
