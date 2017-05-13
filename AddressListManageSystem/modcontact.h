#ifndef MODCONTACT_H
#define MODCONTACT_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDialog>
#include "addrlist.h"
#include "errdlg.h"

namespace Ui {
class Modcontact;
}

class Modcontact : public QDialog
{
    Q_OBJECT

public:
    explicit Modcontact(QWidget *parent = 0);
    ~Modcontact();

private slots:
    void on_apply_clicked();
    void modcontact(QString, QString, QString, QString, QString, QString);

private:
    Ui::Modcontact *ui;
    Errdlg *errdlg;

signals:
    void sendData(QString, QString, QString, QString, QString, QString);
    void error(int);
};

#endif // MODCONTACT_H
