#include "deletedlg.h"
#include "ui_deletedlg.h"

Deletedlg::Deletedlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deletedlg)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

Deletedlg::~Deletedlg()
{
    delete ui;
}

void Deletedlg::on_dapply_clicked()
{
    emit apply();//发送信号
    close();
}
