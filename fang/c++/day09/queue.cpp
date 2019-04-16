#include <iostream>
using namespace std;
//顺序表的队列实现
class Queue{
public:
    Queue(int size = 5) : m_array(new int[size]), m_front(0),
        m_rear(0), m_size(size), m_count(0){}
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
        m_array[m_rear++] = data;
        m_count++;
    }
    //弹出
    int pop(void){
        if (empty())
            throw UnderFlow();
        if (m_front >= m_size)
            m_front = 0;
        m_count--;          
        return m_array[m_front++];
    }
    //判空
    bool empty(void) const{
        return !m_count;
    }
    //判满
    bool full(void) const{
        return m_count == m_size;
    }
private:
    //上溢异常
    class OverFlow : public exception{
        const char* what() const throw(){
            return "队列上溢";
        }
    };
    //下溢异常
    class UnderFlow : public exception{
        const char* what() const throw(){
            return "队列下溢";
        }
    };
    int* m_array;//首地址
    int m_front;//前指针
    int m_rear;//尾指针
    int m_size;//容量
    int m_count;//计数
};
int main (void){
    try{
        Queue queue;
        for (size_t i = 0; !queue.full();i++)
            queue.push(i);
        while (!queue.empty())
            cout << queue.pop() << ' ';
        cout << endl;
    }
    catch(exception& ex){
        cout << ex.what() << endl;
        return -1;
    }
    return 0;
}
