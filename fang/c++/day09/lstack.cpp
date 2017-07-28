#include <iostream>
using namespace std;
//基于链式表的堆栈实现
class Stack{
    public:
        //构造函数中初始化为空堆栈
        Stack(void) : m_top(NULL){}
        //析构过程中销毁剩余节点
        ~Stack(void){
            for (Node* next = NULL; m_top; m_top = next){
                next = m_top->m_next;
                delete m_top;
            }
        }
        //圧入
        void push(int data){
            /*Node* node = new Node;
            node->m_data = data;
            node->m_next = m_top;
            m_top = node;*/
            m_top = new Node(data, m_top);
        }
        //弹出
        int pop (void){
            if (empty())
                throw UnderFlow(); //抛出异常
            //pop出来要销毁栈顶,但要返回栈顶的值,所以需要先把它备份出来.
            int data = m_top->m_data;
            Node* node = m_top->m_next;
            delete m_top;
            m_top = node;
            return data;
        }
        //判空
        bool empty(void) const{
            return !m_top;
        }
    private:
        //下溢异常
        class UnderFlow : public exception{
            const char* what(void) const throw(){
                return "堆栈下溢";
            }
        };
        //节点类
        class Node{
            public:
                Node(int data = 0, Node* next = NULL):
                    m_data(data), m_next(next){}
                int m_data;  //数据
                Node* m_next;//后指针
        };
        Node* m_top; //栈顶
};
int main (void){
    try{
        Stack stack;
        for(int i = 0; i < 10; ++i)
            stack.push(i);
        while(! stack.empty())
            cout << stack.pop() << ' ';
        cout << endl;
    }
    catch (exception& ex){
        cout << ex.what()<< endl;
        return -1;
    }
    return 0;
}
