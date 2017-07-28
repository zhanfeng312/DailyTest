#ifndef  MYTHREAD_H
#define  MYTHREAD_H
#include <QThread> //要把QThread类包括进来
    class  MyThread:public QThread{
        //当有自定义的信号函数或槽函数时,那就必须有这个宏
        Q_OBJECT
        public:
            void run();
            /*自定义信号 用来通知界面发送了那些数据*/
        public:signals: //信号定义出来,不需要实现
               void mySig(QString data);
	}; 
#endif
