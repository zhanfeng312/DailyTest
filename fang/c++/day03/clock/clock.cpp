#include <iostream>
#include <iomanip>
using namespace std;
class Clock {
public:
    Clock(bool timer = true): m_hour(0),m_min(0), m_sec(0) {
        if(! timer) {
            time_t t = time(NULL);   //返回当前时间
            tm* local = localtime(&t);  //把时间当成一个结构体，存放时分秒
            m_hour = local->tm_hour;
            m_min = local->tm_min;
            m_sec = local->tm_sec;
        }
    }
    void run(void){
        for(;;){   //死循环
            show();
            tick();
        }
    }
    //设为私有，外部访问不了
private:
    void show(void){
        cout << '\r' << setfill('0')  //当前行的行首
            << setw(2) << m_hour << ':'
            << setw(2) << m_min << ':'
            << setw(2) << m_sec << flush;  //把缓冲区马上显示出来
    }
    void tick(void){
        sleep(1);
        if(++m_sec == 60) {
            m_sec = 0;
            if(++m_min == 60) {
                m_min = 0;
                if(++m_hour == 24)
                    m_hour = 0;
            }
        }
    }
    int m_hour;
    int m_min;
    int m_sec;
};
int main(void){
    Clock clock;
    clock.run();
    return 0;
}
