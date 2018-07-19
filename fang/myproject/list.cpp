//练习： 实现一个单向线性链表类
//1.建立、测长、正反向打印
//2.逆转 指向相反
//3.获取中间节点值,单次遍历
//4.有序链表的插入和删除
#include <iostream>
#include <stdexcept>
#include <vector>
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
        //反向打印 递归实现
       /* void rprint(void) const{ 
            rprint(m_head);
            cout << endl;
        }*/
        //非递归实现
        void rprint(void) const{
            vector<int> vi;
            Node* node = m_head;
            for (;node; node = node->m_next)
                vi.push_back(node->m_data);
            vector<int>::const_reverse_iterator it = vi.rbegin();
            for (; it != vi.rend(); it++)
                cout << *it << ' ';
            cout << endl;
        }
        void reverse(void){
        }
        //递归实现逆转
        /*
         void reverse(void){
            reverse(m_head);
            swap(m_head, m_tail);
        }
        */
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
       //单链表排序,采用选择排序算法
        void sort(void){
            Node *p1, *small, *q;
            for(p1 = m_head; p1->m_next; p1 = p1->m_next){
                small = p1;
                for(q = p1->m_next; q; q = q->m_next){
                    if (q->m_data < small->m_data)
                        small = q;
                }
                if (small != p1){
                    p1->m_data = small->m_data;
                    //small->m_data = temp;
                }
            }
        }
        //插入data,仍然保持有序
        void insert(int data){
            Node* node = new Node(data);
            //链表为空时,直接插入
            if(!m_head){
                this->append(data);
                return;
            }
            //如果比头节点还小,新节点为头节点
            if(m_head->m_data >= data){
                node->m_next = m_head;
                m_head = node;
                return;
            }
            for(Node* next = m_head;next ;
                    next = next->m_next){
                //如果至少有两个节点,找那个节点的值比它大,就插在它前面
                if(next->m_next){
                    if(next->m_next->m_data >= data){
                        node->m_next = next->m_next;
                        next->m_next = node;
                        return;
                    }
                }
                //如果只有一个节点/循环到最后节点时
                else{
                    if(next == m_head){
                        m_head->m_next = node;
                        node->m_next = next->m_next;
                        return;
                    }
                    next->m_next = node;
                    m_tail = node;
                    return;
                }
            }         
        }
        //删除所有的data,仍然有序
        void remove(int data){
            Node* node, *next = m_head;
            //先判断链表是否有一个节点
            if(next->m_next){
                //判断是否是要删除前面的元素
                if(next->m_data == data){
                    while(next->m_data == data){
                        node = next->m_next;
                        delete next;
                        m_head = next = node;
                    }
                    return;
                }
                //依次遍历,满足条件就删除节点
                else{
                    for(;next->m_next;){
                        if(next->m_next->m_data == data){
                            node = next->m_next->m_next;
                            delete next->m_next;
                            next->m_next = node;
                        }
                        else
                            next = next->m_next;
                    }
                    return;
                }
            }
            //链表只有一个节点
            else{
                //恰好这个节点值等于data，删除
                if(m_head->m_data == data){
                    node = m_head->m_next;
                    delete m_head;
                    m_head = node;
                }
                //如果不等,报错
                else{
                    cout << "没有要删除的元素!" << endl;
                    return;
                }
            }
        }
    private:
        class Node{
            public:
                Node(int data = 0, Node* next = NULL) :
                    m_data(data), m_next(next){}
                int m_data;
                Node* m_next;
        };
        void rprint(Node* head) const{
            if (head){
                rprint(head->m_next); //函数栈
                cout << head->m_data << ' ';
            }
        }
        /*void reverse(Node* head){
            if (head && head->m_next){
                reverse(head->m_next);
                head->m_next->m_next = head;
                head->m_next = NULL;
            }
        }
        */
        Node* m_head;
        Node* m_tail;
};
int main(void){
    List list;
    list.append(5);
    list.append(4);
    list.append(3);
    
    cout << list.size() << endl; //3
    list.print();  //5 4 3
    list.rprint(); //3 4 5
    /*cout << list.middle()<< endl; //4
    list.sort();

    list.insert(8);
    list.print(); //3 4 5 8 
    list.insert(0);
    list.insert(0);
    list.insert(10);
    list.insert(5);
    list.print(); //0 0 3 4 5 5 8 10
    list.remove(0);
    list.print(); //3 4 5 5 8 10
    list.remove(4); //3 5 5 8 10
    list.insert(10);
    list.remove(5);
    list.print(); //3 8 10 10
    list.remove(10);
    list.remove(3);
    list.print(); //8

    list.insert(6);
    list.print();//6 8 
    */
    return 0;
}
