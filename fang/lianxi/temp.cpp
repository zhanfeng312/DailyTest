#include <iostream>
using namespace std;
template <typename T>
class List{
    public:
        //构造初始化链表
        List(void) : m_head(NULL), m_tail(NULL){}
        //析构释放节点
        ~List(void){
            for (Node* node;m_head;m_head = node){
                node = m_head->m_next;
                delete m_head;
            }
        }
        //插入
        void insert(T data){
            Node* node = new Node(data);
            if (!m_head)
                m_head = node;
            else
              m_tail->m_next = node;
            m_tail = node;
        }
        //打印
        void print(){
            for (Node* node = m_head; node;
                    node = node->m_next)
                cout << node->m_data << ' ';
            cout << endl;
        }
    private:
        class Node{
            public:
                Node(T data = 0 , Node* node = NULL) : 
                    m_next(node), m_data(data){}            
                T m_data; //数据域
                Node* m_next; //指针域
        };
        Node* m_head; //头指针
        Node* m_tail; //尾指针
};
int main (void){
    List<int> l;
    l.insert(12);
    l.insert(17);
    l.insert(14);
    l.insert(13);
    l.print();
    return 0;
}
