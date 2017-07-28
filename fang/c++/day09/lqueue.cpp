#include <iostream>
using namespace std;
//基于链式表实现的队列
class Queue{
    public:
        //在构造过程中初始化为空队列
        Queue(void) : m_rear(NULL), m_front(NULL){}
        //在析构过程中销毁剩余的节点
        ~Queue(void){
            for (Node* next; m_front; m_front = next){
                next = m_front->m_next;
                delete m_front;
            }
        }
        //圧入
        void push(int data){
            Node* node = new Node(data);
            if (m_rear)
                m_rear->m_next = node;
            else
                m_front = node;
            m_rear = node;
        }
        //弹出
        int pop(void){
            if (empty())
                throw UnderFlow();
            int data = m_front->m_data;//把它的值先取出来
            Node* next = m_front->m_next;
            delete m_front;
            if (!(m_front = next))
                m_rear = NULL;
            return data;
        }
        //判空
        bool empty(void) const{
            return ! m_front && !m_rear;
        }
    private:
        //下溢异常
        class UnderFlow : public exception {
            const char* what(void) const throw(){
                return "队列下溢";
            }
        };
        //节点
        class Node{
            public:
                Node(int data = 0, Node* next = NULL):
                    m_data(data), m_next(next){}
                int m_data; //数据
                Node* m_next; //后指针
        };
        Node* m_rear;  //后端
        Node* m_front; //前端
};
int main(void){
    try{
        Queue queue;
        for(int i = 0; i < 20; ++i)
            queue.push(i);
        while(! queue.empty())
            cout << queue.pop() << endl;
        cout << endl;
    }
    catch(exception& ex){
        cout << ex.what() << endl;
        return -1;
    }
    return 0;
}
