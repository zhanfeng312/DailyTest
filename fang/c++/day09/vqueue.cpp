#include <iostream>
using namespace std;
//基于顺序表的队列
class Queue{
    public:
        //构造过程中分配内存
        Queue(size_t size = 5) :
            m_array(new int[size]), m_size(size),
            m_rear(0), m_front(0), m_count(0){}
        //析构函数中释放内存
        ~Queue(void){
            if (m_array){
                delete[] m_array;
                m_array = NULL;
            }
        }
        //圧入
        void push(int data){
            if (full())
                throw OverFlow();
            if (m_rear >= m_size)
                m_rear = 0;
            ++m_count;
            m_array[m_rear++] = data; //逻辑保证
        }
        //弹出
        int pop(void){
            if (empty())
                throw UnderFlow(); //抛出一个匿名对象
            if (m_front >= m_size)
                m_front = 0;
            --m_count;
            return m_array[m_front++];
        }
        //判空
        bool empty(void) const {
            return !m_count;
        }
        //判满
        bool full (void) const {
            return m_count == m_size;
        }
    private:
        //上溢异常
        class OverFlow : public exception{
            const char* what(void) const throw(){
                return "队列上溢";
            }
        };
        //下溢异常
        class UnderFlow : public exception{
            const char* what(void) const throw(){
                return "队列下溢";
            }
        };
        int *m_array;   //数组
        size_t m_size;  //容量
        size_t m_rear;  //后端
        size_t m_front; //前端
        size_t m_count; //计数
};
int main(void){
    try{
        Queue queue;
        queue.push(10);
        queue.push(20);
        queue.push(30);
        queue.push(40);
        queue.push(50);
        //queue.push(60); //上溢异常
        cout << queue.pop() << endl; //10
        queue.push(60);
        cout << queue.pop() << endl; //20
        queue.push(70);
        //queue.push(80);
        cout << queue.pop() << endl; //30
        cout << queue.pop() << endl; //40
        cout << queue.pop() << endl; //50
        cout << queue.pop() << endl; //60
        cout << queue.pop() << endl; //70
        //cout << queue.pop() << endl;//下溢异常
    }
    catch (exception& ex){
        cout << ex.what() << endl;
        return -1;
    }
    return 0;
}
