#ifndef DELETEDLG_H
#define DELETEDLG_H

#include <QDialog>

namespace Ui {
class Deletedlg;
}

class Deletedlg : public QDialog
{
    Q_OBJECT

public:
    explicit Deletedlg(QWidget *parent = 0);
    ~Deletedlg();

private slots:
    void on_dapply_clicked();

private:
    Ui::Deletedlg *ui;

signals:
    void apply();
};

#endif // DELETEDLG_H
