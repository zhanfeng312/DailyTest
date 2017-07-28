#include <QApplication>
#include <QLabel>  //为了可见
#include <QObject>
#include <QTextCodec>
int main(int argc, char** argv) {
    /*构建qt应用程序对象*/
    QApplication app(argc, argv);
    /*得到编码对象*/
    QTextCodec *coder = QTextCodec
        ::codecForName("utf-8");
    /*设置编码对象*/
    QTextCodec::setCodecForTr(coder);
    /*构建标签*/
    QLabel qlab(QObject::tr("你好 qt!", "utf-8"));
    qlab.show();
    /*让程序进入事件循环*/
    return app.exec();
}

