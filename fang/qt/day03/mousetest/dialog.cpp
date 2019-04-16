#include "dialog.h"
#include "ui_dialog.h"
#include<QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}
#include <QMouseEvent>
#include<QCursor>
#include<QPoint>
void Dialog::mousePressEvent
(QMouseEvent *e){
    QPoint qp = QCursor::pos(); //光标的位置不依赖界面
    switch(e->button()){
    case Qt::LeftButton:
        qDebug("left button clicked %d:%d",
               e->x(),e->y()); //打印按下的位置
        qDebug("cursor %d:%d",
               qp.x(),qp.y());
        break;
    case Qt::RightButton:
        qDebug("right button clicked %d:%d",
               e->x(),e->y());
        break;
    case Qt::MidButton:
        qDebug("mid button clicked %d:%d",
               e->x(),e->y());
        break;
    }
}
void Dialog::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case Qt::Key_Left:
        qDebug("left key pressed");
        break;
    case Qt::Key_Down:
        qDebug("down key pressed");
        break;
    case Qt::Key_Right:
        qDebug("right key pressed");
        break;
    case Qt::Key_Up:
        //qDebug("up key pressed");
        qDebug()<<"uo key pressed";
        break;
    }
}

Dialog::~Dialog()
{
    delete ui;
}
