#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
/*
class Adder : public QDialog{  //公有继承
    private:
        QLineEdit   *add; //加数
        QLabel      *oper;
        QLineEdit   *added;
        QPushButton *equ;
        QLineEdit   *res;
    public:
        Adder();
        ~Adder();
};
*/
#include "adder.h"
Adder::Adder(){
    this->resize(670, 300);
    //设置组件
    add  = new QLineEdit(this);
    oper = new QLabel("+", this);
    added= new QLineEdit(this);
    equ  = new QPushButton("=", this);
    res  = new QLineEdit(this);
    //组件移到合适的位置
    add-> move(20, 120);
    oper-> move(170, 120);
    added->move(220, 120);
    equ-> move(370, 120);
    res->move(480, 120);
    connect(equ, SIGNAL(clicked()), this, SLOT(getRes()));
}
Adder::~Adder(){
    delete add;
    delete oper;
    delete added;
    delete equ;
    delete res;
}
void Adder::getRes(){
    /*
    qDebug("this is complete calculator");
    //res->setText(add->selectedText()+ added->selectedText());
    QString qadd = add->text();
    QString qadded = added->text();
    int iadd=qadd.toInt();
    int iadded=qadded.toInt();
    int ires = iadd + iadded;
    res->setText(QString::number(ires));
    */
    res->setText(QString::number(
                add->text().toInt()+added->text().toInt()));
}
