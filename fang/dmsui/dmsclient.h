#ifndef  DMSCLIENT_H
#define  DMSCLIENT_H
/*这个是界面*/
#include <QDialog>
#include <QTextBrowser> //文本显示区域
#include <QPushButton>
#include "mythread.h"
    class  DmsClient:public QDialog{
        Q_OBJECT
        private:
            QTextBrowser  *showdata;//显示文本区域指针
            QPushButton   *bstart;
            QPushButton   *bclose;
	    /*和界面绑定的线程指针*/
	    MyThread *myth;
        public:
            DmsClient();
            ~DmsClient();
        public slots:
	    void startClient(); 		
        /*接收线程的信号 数据*/
        //槽函数如何设计?参数类型和个数须一样
        public slots:
	    void getData(QString data);			
	};
#endif




