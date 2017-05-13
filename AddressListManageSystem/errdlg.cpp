#include "errdlg.h"
#include "ui_errdlg.h"

Errdlg::Errdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Errdlg)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

Errdlg::~Errdlg()
{
    delete ui;
}

void Errdlg::stack(int i){
    ui->stackedWidget->setCurrentIndex(i);//切换到指定页面
}
