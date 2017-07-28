#ifndef YAOJIANG_H
#define YAOJIANG_H
#include<QTimer>
#include <QDialog>
#include <QImage>
namespace Ui {
class YaoJiang;
}

class YaoJiang : public QDialog
{
    Q_OBJECT
    
public:
    explicit YaoJiang(QWidget *parent = 0);
    ~YaoJiang();
    
private:
    Ui::YaoJiang *ui;
    /*要绘制的图片*/
    QImage img;
    /*图片的编号*/
    int imgind;
    /*定时器指针 用来定时发出timeout信号*/
    QTimer *timer;
    /*参与摇奖的人*/
    QString names[5];
    /*绘制标志*/
    bool pflag;
    /*增加控制标志的槽函数*/
public slots:
    void changFlag();
    /*槽函数 定时重画界面
public slots:
    void myrepaint();*/
    /*绘制事件处理函数*/
public:
    void paintEvent(QPaintEvent *);
public:
    /*定时器事件处理函数*/
    void timerEvent(QTimerEvent *);
};

#endif // YAOJIANG_H
