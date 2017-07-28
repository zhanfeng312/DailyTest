#include <QApplication>
#include <QDialog>
#include <QSlider>
#include <QSpinBox>
#include <QObject>
int main (int argc, char **argv) {
    QApplication app (argc, argv);
    QDialog *parent;
    QSlider *qsli;
    QSpinBox *qspin;
    parent = new QDialog();
    parent->resize(600, 300);
    qsli = new QSlider(parent);
    qspin = new QSpinBox(parent);
    /*调整组件的位置*/
    qsli->move(50, 50);
    qspin->move(300, 200);
    qsli->resize(20, 200);
    //qspin->setValue(98);
    parent->show();
    /*滑块对象去影响微调框*/
    QObject::connect(qsli, SIGNAL(valueChanged(int)), qspin, SLOT(setValue(int)));
    QObject::connect(qspin, SIGNAL(valueChanged(int)), qsli, SLOT(setValue(int)));
    qDebug("this is output"); //printf换成qDebug
    return app.exec();
}
