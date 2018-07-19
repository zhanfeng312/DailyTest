#ifndef ADDER_H
#define ADDER_H
#include "jfq.h"
class Adder : public QDialog{
    Q_OBJECT
    private:
        Ui_Dialog *ui;  //定义一个ui属性
    public:
        Adder();
        ~Adder();
        /*得到结果*/
        public slots:
            void getRes();
};
#endif
