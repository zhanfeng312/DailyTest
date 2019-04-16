#ifndef ADDER_H
#define ADDER_H

#include <QDialog>

namespace Ui {  //命名空间
class Adder;
}

class Adder : public QDialog
{
    Q_OBJECT
    
public:
    explicit Adder(QWidget *parent = 0);
    ~Adder();
    /*完成计算功能*/
public slots:
        void getRes();
private:
    Ui::Adder *ui;
};

#endif // ADDER_H
