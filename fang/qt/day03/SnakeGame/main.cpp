#include<QApplication>
#include<snakegame.h>
int main(int argc, char** argv){
    QApplication app (argc, argv);
    SnakeGame sg;
    sg.show();
    return app.exec();
}
