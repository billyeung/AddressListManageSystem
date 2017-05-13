#ifndef NEWCONTACT_H
#define NEWCONTACT_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDialog>
#include "addrlist.h"
#include "errdlg.h"

namespace Ui {
class Newcontact;
}

class Newcontact : public QDialog
{
    Q_OBJECT

public:
    explicit Newcontact(QWidget *parent = 0);
    ~Newcontact();

private slots:
    void on_apply_clicked();

private:
    Ui::Newcontact *ui;
    Errdlg *errdlg;

signals:
    void sendData(QString,QString,QString,QString,QString,QString);
    void error(int);
};

#endif // NEWCONTACT_H
