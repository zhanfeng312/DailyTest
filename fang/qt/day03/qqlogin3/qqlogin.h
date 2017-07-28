#ifndef QQLOGIN_H
#define QQLOGIN_H

#include <QDialog>

namespace Ui {
class QqLogin;
}

class QqLogin : public QDialog
{
    Q_OBJECT
    
public:
    explicit QqLogin(QWidget *parent = 0);
    ~QqLogin();
    /*处理登陆和退出*/
public slots:
    void loginAndCancel();
    
private:
    Ui::QqLogin *ui;
};

#endif // QQLOGIN_H
