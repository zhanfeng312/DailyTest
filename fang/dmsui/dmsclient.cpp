#include "dmsclient.h"
DmsClient::DmsClient(){
    this->resize(500,500);
    showdata=new QTextBrowser(this);
    bstart=new QPushButton("start",this);
    bclose=new QPushButton("close",this);
    showdata->resize(440,390);
    showdata->move(30,30);
    bstart->move(100,450);
    bclose->move(350,450);	
    /*创建线程对象*/
    myth = new MyThread();
    /*绑定线程 到界面*/
    connect(myth, SIGNAL(mySig(QString)), this,
            SLOT(getData(QString)));
    /*连接按钮到槽函数*/
    connect(bstart,SIGNAL(clicked()),this,
	    SLOT(startClient()));
    connect(bclose,SIGNAL(clicked()),this,
	    SLOT(close()));
}
DmsClient::~DmsClient(){
    delete  showdata;
    delete  bstart;
    delete  bclose;
}
/*把耗时的操作交给线程*/
void* processData(void* par){
    QTextBrowser *showdata=(QTextBrowser*)par;	
    sleep(1);  //消耗时间
    showdata->append("send data to server");
    sleep(1);
    showdata->append("send data to server");
    sleep(1);
    showdata->append("send data to server");
    sleep(1);
    showdata->append("send data to server");
    sleep(1);
    showdata->append("send over!");
    return  par; //没啥用
}
void DmsClient::startClient(){
    showdata->append("start client");
    /*用线程来处理耗时操作*/
    //pthread_t  thid;
    //pthread_create(&thid, 0, processData, showdata);  //传参
    /*启动线程*/
    myth->start();
    //bstart->setDisabled(true);
}
void DmsClient::getData(QString data){
    showdata->append(data);
}



