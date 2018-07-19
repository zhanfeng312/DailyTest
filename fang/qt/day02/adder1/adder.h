#ifndef ADDER_H
#define ADDER_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
class Adder : public QDialog{  //公有继承
    Q_OBJECT;
    private:
        QLineEdit   *add;  //加数
        QLabel      *oper; //操作符
        QLineEdit   *added;//被加数
        QPushButton *equ;  //=
        QLineEdit   *res; //结果
    public:
        Adder();
        ~Adder();
        public slots:
        /*实现计算功能*/
        void getRes();
};
#endif
