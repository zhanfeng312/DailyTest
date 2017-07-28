#include <iostream>
#include "lstack.h"
using namespace std;
//基于堆栈的队列
class Queue{
    public:
        //圧入
        void push(int data){
            m_i.push(data);
        }
        //弹出
        int pop (void){
            if (m_o.empty()){
                if(m_i.empty())
                    throw underflow_error("队列下溢");
                while(! m_i.empty())
                    m_o.push(m_i.pop());
            }
            return m_o.pop();
        }
        //判空
        bool empty(void) const {
            return m_i.empty() && m_o.empty();
        }
    private:
        Stack m_i;  //输入栈
        Stack m_o;  //输出栈
};
int main(void){
    try{
        Queue queue;
        for (int i = 0; i < 10; ++i)
            queue.push(i);
        cout << queue.pop() << endl; //0
        cout << queue.pop() << endl; //1
        cout << queue.pop() << endl; //2
        cout << queue.pop() << endl; //3
        cout << queue.pop() << endl; //4
        queue.push(10);
        queue.push(11);
        queue.push(12);
        while(!queue.empty())
            cout << queue.pop() << endl;
    }
    catch(exception& ex){
        cout << ex.what() << endl;
        return -1;
    }
    return 0;
}
