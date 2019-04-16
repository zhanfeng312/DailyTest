#ifndef MYTIME_H
#define MYTIME_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
class Mytime : public QDialog{
    Q_OBJECT;   //自定义信号函数时,要声明这个宏
    private:
        QLabel *timeres;
        QPushButton *gettime;
    public:
        Mytime();
        ~Mytime();
        public slots:
            void setTime();
};
#endif
