#include <QApplication>
#include <QLabel>  //为了可见
int main(int argc, char** argv) {
    /*构建qt应用程序对象*/
    QApplication app(argc, argv);
    /*构建标签*/
    QLabel qlab("hello qt!");
    qlab.show();
    /*让程序进入事件循环*/
    return app.exec();
}

