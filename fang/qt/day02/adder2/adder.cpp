#include "adder.h"
Adder::Adder(){
    /*给界面赋值*/
    ui = new Ui_Dialog();
    /*加载界面过程都一样*/
    ui->setupUi(this);
    /*要访问界面通过ui访问*/
    connect(ui->button, SIGNAL(clicked()), this, SLOT(getRes()));
}
Adder::~Adder(){
    delete ui;
}
void Adder::getRes(){
    /*要访问界面通过ui访问*/
    ui->line3->setText(QString::number(
                ui->line1->text().toInt()+
                ui->line2->text().toInt()));
}
