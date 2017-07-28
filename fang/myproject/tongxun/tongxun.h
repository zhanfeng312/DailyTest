#ifndef _TONGXUN_H
#define _TONGXUN_H
#include <string>
using namespace std;
//基于单链表的通讯录实现
class TongXun{
    public:
        //构造函数使表头,表尾节点为空
        TongXun(void);
        //析构函数销毁所有节点
        ~TongXun(void);
        //增加联系人信息
        void add();
        //显示全部联系人信息
        void list(); 
        //查找联系人信息
        void look();        
        //修改联系人信息
        void change();
        //删除联系人
        void remove();
    private:
        class Node{
            public:
                Node(string num = "", string name = "", Node* next = NULL):
                    m_num(num), m_name(name), m_next(next){}
                string m_num;
                string m_name;
                Node* m_next;
        };
        Node* m_head; //表头指针
        Node* m_tail; //表尾指针
};
#endif  //TONGXUN_H
