#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QObject>
int main(int argc, char** argv) {
    QApplication app(argc, argv);   //app窗口
    /*做一个父窗口*/
    QWidget *parentw=new QWidget();
    parentw->resize(500, 400);     //设置父窗口大小
    QLabel qlab("hello, qt!",parentw);      //标签
    QPushButton qpush("closelab", parentw); //按钮
    /*移动按钮*/
    qpush.move(200, 300);
    /*移动标签到200 50*/
    qlab.move(200, 50);
    parentw->show();
    /*增加功能,要求点击按钮，关闭标签
    QObject::connect(&qpush,SIGNAL(clicked()), &qlab, SLOT(close()));*/
    /*关联到父窗口上*/
    QObject::connect(&qpush, SIGNAL(clicked()), parentw,SLOT(close()));
    return app.exec();
}
