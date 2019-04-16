#include "qqlogin.h"
#include "ui_qqlogin.h"

QqLogin::QqLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QqLogin)
{
    ui->setupUi(this);
    connect(ui->login, SIGNAL(clicked()),
            this, SLOT(loginAndCancel()));
    connect(ui->cancel, SIGNAL(clicked()),
            this, SLOT(loginAndCancel()));
}

QqLogin::~QqLogin()
{
    delete ui;
}
void QqLogin::loginAndCancel(){
    if(((QPushButton*)sender())
            ->objectName() == "login"){
    }
    if(((QPushButton*)sender())
            ->objectName() == "cancel"){
        this->close();
    }

}
