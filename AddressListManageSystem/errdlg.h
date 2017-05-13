#ifndef ERRDLG_H
#define ERRDLG_H

#include <QDialog>

namespace Ui {
class Errdlg;
}

class Errdlg : public QDialog
{
    Q_OBJECT

public:
    explicit Errdlg(QWidget *parent = 0);
    ~Errdlg();

private slots:
    void stack(int);
private:
    Ui::Errdlg *ui;
};

#endif // ERRDLG_H
