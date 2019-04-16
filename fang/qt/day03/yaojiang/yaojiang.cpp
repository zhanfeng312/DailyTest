#include "yaojiang.h"
#include "ui_yaojiang.h"
#include<QTime>
YaoJiang::YaoJiang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YaoJiang)
{
    qsrand(QTime::currentTime().msec());
    ui->setupUi(this);
    /*初始化数组*/
    names[0] = "zhao";
    names[1] = "lu";
    names[2] = "beauty";
    names[3] = "zhao";
    names[4] = "lu";
    pflag = false;
    /*制造定时器事件*/
    this->startTimer(500);

    /*构建定时器
    timer = new QTimer(); //初始化
    timer->setInterval(500); //200毫秒， 1000就是1秒
    //timer->start();  //启动定时器
    connect(timer, SIGNAL(timeout()),
            this, SLOT(repaint()));*/
    connect(ui->bstart, SIGNAL(clicked()),
            this, SLOT(changFlag()));
    connect(ui->bstop, SIGNAL(clicked()),
            this, SLOT(changFlag()));
}

YaoJiang::~YaoJiang()
{
    delete ui;
}
/**点击start pflag = true
       stop pflag = false*/
void YaoJiang::changFlag(){
    if (((QPushButton*)sender())->objectName()
            == "bstart"){
        pflag = true;
    }
    if (((QPushButton*)sender())->objectName()
            == "bstop"){
        pflag = false;
    }
}
#include <QPainter>
void YaoJiang::paintEvent(QPaintEvent *){
    QPainter qp(this);
    if (pflag){
    qp.drawLine(0,0,400,600); //画线
    /*显示图片的代码*/
    imgind = (qrand() % 5) + 1; //随机数
    QString imgstr = ":/images2/"; //字符串

    imgstr+=QString::number(imgind); //把数字转换成字符串
    imgstr+=".jpg";
    img.load(imgstr); //加载
    /*缩放*/
    img = img.scaled(300, 400);

    qp.drawImage(40, 40, img, 0, 0,
                 300, 400); //40,40为起始位
    ui->personName->setText(names[imgind-1]);
    }
    qp.drawImage(40, 40, img, 0, 0,
                 300, 400); //40,40为起始位
}
void YaoJiang::timerEvent(QTimerEvent *){
    repaint();
}
