#include "abdlg.h"
#include "ui_abdlg.h"

Abdlg::Abdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Abdlg)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

Abdlg::~Abdlg()
{
    delete ui;
}
