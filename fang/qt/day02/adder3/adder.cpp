#include "adder.h"
#include "ui_adder.h"

Adder::Adder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Adder)
{
    ui->setupUi(this);
    /*连接*/
    connect(ui->equ, SIGNAL(clicked()),
            this, SLOT(getRes()));
}

Adder::~Adder()
{
    delete ui;
}
/*只用写实现代码*/
void Adder::getRes(){
    ui->res->setText(QString::
           number(ui->add->text().toInt()+
            ui->added->text().toInt()));
}
