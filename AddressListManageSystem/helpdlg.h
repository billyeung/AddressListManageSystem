#ifndef HELPDLG_H
#define HELPDLG_H

#include <QDialog>

namespace Ui {
class Helpdlg;
}

class Helpdlg : public QDialog
{
    Q_OBJECT

public:
    explicit Helpdlg(QWidget *parent = 0);
    ~Helpdlg();

private:
    Ui::Helpdlg *ui;
};

#endif // HELPDLG_H
