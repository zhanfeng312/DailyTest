#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include "mytime.h"
/*
class Time : public QDialog{
    private:
        QLabel *timeres;
        QPushButton *gettime;
    public:
        Time();
        ~Time();
};
*/
Mytime::Mytime(){
    this->resize(400, 500); //主窗口的大小
    timeres = new QLabel("current time", this);
    gettime = new QPushButton ("get time", this);
    timeres->move(150, 50);
    gettime->move(150, 400);
    connect(gettime, SIGNAL(clicked()),
            this, SLOT(setTime()));
    /*连接自定义信号和目标的槽函数*/
    connect(this, SIGNAL(mySig(QString)),
            timeres, SLOT(setText(QString)));
}
Mytime::~Mytime(){
    delete timeres;
    delete gettime;
}
#include <QTime>
void Mytime::setTime(){
    /*调用了QLabel的槽函数*/
    QString timestr = QTime::currentTime().
            toString("hh:mm:ss");//返回当前时间对象
    //timeres->setText(timestr);
    /*发射一个信号*/
    emit mySig(timestr);
}
