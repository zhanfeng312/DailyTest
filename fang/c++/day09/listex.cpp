//练习： 实现一个单向线性链表类
//1.建立、测长、正反向打印
//2.逆转 指向相反
//3.获取中间节点值,单次遍历
//4.有序链表的插入和删除
#include <iostream>
//标准异常类
#include <stdexcept>
using namespace std;
class List{
    public:
        //构造初始化链表
        List(void) : m_head(NULL), m_tail(NULL){}
        //释放剩余的节点
        ~List(void){
            for(Node* next; m_head;m_head = next){
                next = m_head->m_next;
                delete m_head;
            }
        }
        //增加
        void append(int data){
            Node* node = new Node(data);
            if (m_tail)
                m_tail->m_next = node;
            else
                m_head = node;
            m_tail = node;
        }
        //测长
        size_t size(void) const {
            size_t count = 0;
            for(Node* next = m_head; next; 
                    next = next->m_next)
                ++count;
            return count;
        }
        //正向打印
        void print(void) const{
            for (Node* next = m_head; next;
                    next = next->m_next)
                cout << next->m_data << ' ';
            cout << endl;
        }
        //反向打印
        void rprint(void) const{ 
            rprint(m_head);
            cout << endl;
        }
        //递归实现逆转
        /*void reverse(void){
            reverse(m_head);
            swap(m_head, m_tail);
        }*/
        //非递归实现逆转
        void reverse(void){
            //当前只有一个节点时,没必要逆转
            if(m_head != m_tail){
                Node* p0 = NULL;
                Node* p1 = m_tail = m_head;
                Node* p2 = p1 ? p1->m_next : NULL;
                while (p2 != NULL){
                    Node* node = p2->m_next; //先备份一下
                    p1->m_next = p0;
                    p2->m_next = p1;

                    p0 = p1;
                    p1 = p2;
                    p2 = node;
                }
                m_head = p1;
            }
        }
        //获取中间值
        int middle(void) const{
            if (! m_head || ! m_tail)
                throw underflow_error("链表下溢!");
            if (m_head == m_tail)
                return m_head->m_data;
            Node* mid = m_head;
            for(Node* node = m_head;
                    node->m_next && node->m_next->m_next;
                    node = node->m_next->m_next)
                mid = mid->m_next;
            return mid->m_data;
        }
        //用选择排序
        void sort(void) {
            Node *p, *q, *small;
            for (p = m_head; p; p = p->m_next){
                small = p;
                for (q = p->m_next; q; q = q->m_next)
                    if (q->m_data < small->m_data)
                        small = q;
                if (small != p){
                    int temp = small->m_data;
                    small->m_data = p->m_data;
                    p->m_data = temp;
                }
            }
        }
        //插入data,仍然保持有序i
        void insert(int data){
        }
        //删除所有的data
        void remove(int data){
        }
    private:
        //节点类
        class Node{
            public:
                Node(int data = 0, Node* next = NULL) :
                    m_data(data), m_next(next){}
                int m_data; //节点数据
                Node* m_next;//后指针
        };
        void rprint(Node* head) const{
            if (head){
                rprint(head->m_next);
                cout << head->m_data << ' ';
            }
        }
        void reverse(Node*& head){
            if (head && head->m_next){
                reverse(head->m_next);
                head->m_next->m_next = head;
                head->m_next = NULL;
            }
        }
        Node* m_head;//头指针
        Node* m_tail;//尾指针
};
int main(void){
    List list;
    for(int i = 0; i < 10; ++i)
        list.append(i);
    list.append(-1);
    cout << list.size() << endl;
    cout << "************************" << endl;
    list.print();
    list.rprint();
    cout << "************************" << endl;
    list.reverse();
    list.print();
    cout << "************************" << endl;
    cout << list.middle() << endl;
    list.sort();
    list.print();
    return 0;
}
