#include "mythread.h"
#include "../logreader.h"
#include "../logsender.h"
#include <stdio.h>
void  MyThread::run(){
    /*在这里实现线程的功能*/
    qDebug("send data to server");//直接打印在屏幕上
    /*通知界面发送了那些数据*/
    emit mySig("send data to server");//执行这个信号函数
    sleep(1);
    qDebug("send data to server");
    emit mySig("send data to server");
    sleep(1);
    qDebug("send data to server");
    emit mySig("send data to server");
    sleep(1);
    qDebug("send data to server");
    emit mySig("send data to server");
    sleep(1);
    /*LogReader  logreader;
    LogSender  logsender;
    list<MatchedLogRec> matches=
        logreader.readLogs();
    *如果发送一个集合 不能把具体的数据通知界面*
    //logsender.sendMatches(&matches);
    你能拿到每次发送的数据吗？
    logsender.initNetWork();
    while(matches.size()>0){
        sleep(1);		 
	MatchedLogRec  mlog=*(matches.begin());	 
        bool f= logsender.sendMatche(mlog);      
	if(f){
	*把发送的数据组织成字符串 通知界面*
            char  datastr[100];
            sprintf(datastr,"%s:%d:%d",
                    mlog.logname,mlog.pid,mlog.logintime);
		    emit mySig(QString(datastr));
		    matches.erase(matches.begin());
        }else{
            break;
        }
    }
    logsender.closefd();
    */
}






