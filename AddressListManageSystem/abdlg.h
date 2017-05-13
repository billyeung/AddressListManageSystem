#ifndef ABDLG_H
#define ABDLG_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QDialog>

namespace Ui {
class Abdlg;
}

class Abdlg : public QDialog
{
    Q_OBJECT

public:
    explicit Abdlg(QWidget *parent = 0);
    ~Abdlg();

private:
    Ui::Abdlg *ui;
};

#endif // ABDLG_H
