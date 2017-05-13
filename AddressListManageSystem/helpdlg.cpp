#include "helpdlg.h"
#include "ui_helpdlg.h"

Helpdlg::Helpdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Helpdlg)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

Helpdlg::~Helpdlg()
{
    delete ui;
}
