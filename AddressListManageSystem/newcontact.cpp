#include "newcontact.h"
#include "ui_newcontact.h"

Newcontact::Newcontact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Newcontact)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

Newcontact::~Newcontact()
{
    delete ui;
}

void Newcontact::on_apply_clicked()
{
    if(ui->name->text().isEmpty()){//如果姓名为空
        errdlg = new Errdlg(this);
        connect(this,SIGNAL(error(int)),errdlg,SLOT(stack(int)));
        emit error(0);
        errdlg->exec();
        return;
    }
    if((!isDigitStr(ui->pnum->text()))||(!isDigitStr(ui->qnum->text()))||((!ui->email->text().isEmpty())&&ui->email->text().indexOf("@")<0)) {//如果数据格式不正确
        errdlg = new Errdlg(this);
        connect(this,SIGNAL(error(int)),errdlg,SLOT(stack(int)));
        emit error(1);
        errdlg->exec();
        return;
    }
    QString group;
    switch(ui->group->currentIndex())
    {
    case 0:
        group = "de";
        break;
    case 1:
        group = "fa";
        break;
    case 2:
        group = "fr";
        break;
    case 3:
        group = "co";
        break;
    }
    emit sendData(ui->name->text(),ui->pnum->text(),ui->qnum->text(),ui->email->text(),ui->address->toPlainText(),group);//发送信号
    close();
}
