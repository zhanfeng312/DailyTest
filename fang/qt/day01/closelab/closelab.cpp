#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QObject>
int main (int argc, char** argv) {
    QApplication app (argc, argv);
    //QLabel qlab("hello qt!");
    QPushButton *qpush = new QPushButton("close lab");
    //qlab.show(); //显示出来
    qpush->show();
    /*
    //实现功能,点击按钮关闭标签
    QObject::connect(qpush, SIGNAL(clicked()),
            &qlab,SLOT(close()));
    QObject::connect(qpush, SIGNAL(clicked()),
            qpush,SLOT(close()));
    */
    QObject::connect(qpush,SIGNAL(clicked()),
            &app,SLOT(quit()));
    return app.exec();
}
