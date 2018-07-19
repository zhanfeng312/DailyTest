#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include<QLabel>
#include<QDialog>
#include<QTimer>
#include<QKeyEvent>
enum Direction{D_UP, D_DOWN, D_LEFT, D_RIGHT};
class SnakeGame : public QDialog{
    Q_OBJECT
private:
    QLabel* food;  //食物
    QList<QLabel*> snake; //贪吃蛇链表
    int footLen;   //歩长
    QTimer* timer; //定时器
    Direction dire;//方向
    int maxLen;    //最大长度
public:
    SnakeGame();
    ~SnakeGame();
    /*使用键盘方向键控制方向*/
public:
    void keyPressEvent(QKeyEvent *e);
    /*蛇根据方向移动调用一次移动一个歩长*/
public slots:
    void snakeMove();
    /*产生食物的函数*/
    QLabel* getFood();
};

#endif // SNAKEGAME_H
