#include "qqlogin.h"
//构造函数
QqLogin::QqLogin():ui(new Ui_calculator())/*初始化列表*/ {
    //ui = new Ui_calculator();
    ui->setupUi(this);  //加载界面
    connect(ui->login, SIGNAL(clicked()),
            this, SLOT(loginAndCancel()));
    connect(ui->cancel, SIGNAL(clicked()),
            this, SLOT(loginAndCancel()));
}
QqLogin::~QqLogin(){
    delete ui;
}
/*既服务登陆又负责退出*/
#include <QMessageBox>
void QqLogin::loginAndCancel(){
    /*按钮的判断*/
    if (((QPushButton*)sender())->objectName()
            =="login"){
        if(ui->uname->text() == "abc" &&/*and 标准*/
                ui->upasswd->text() == "123"){
            qDebug("login success!");
        }
    }
    if(((QPushButton*)sender())->objectName()
            =="cancel"){
        QMessageBox msg; //构建一个QMessageBox
        msg.setText("are you sure?");
        msg.setStandardButtons(
                QMessageBox::Yes|QMessageBox::No); //设置按下cancel后的选项
        if(msg.exec() == QMessageBox::Yes){
            this->close();
        }
    }

}
