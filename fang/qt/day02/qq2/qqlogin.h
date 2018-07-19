#ifndef QQLOGIN_H
#define QQLOGIN_H
#include "qq.h"
class QqLogin: public QDialog{
    Q_OBJECT
    private:
    Ui_calculator *ui;
    public:
    QqLogin(); //构造函数
    ~QqLogin();//析构函数
    /*既服务登陆又负责取消*/
    public slots: //槽函数
        void loginAndCancel();    
};
#endif

