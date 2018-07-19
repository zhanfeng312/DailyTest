#include "tongxun.h"
#include <iostream>
#include <fstream>
string name;
string num;
//构造函数使表头,表尾节点为空
TongXun::TongXun(void) : m_head(NULL), m_tail(NULL){}
//析构函数销毁所有节点
TongXun::~TongXun(void){
    for(Node* node = m_head; node; node = node->m_next)
        delete node;
}
//增加联系人信息
void TongXun::add(){
    cout << "请输入电话号码:";
    cin >> num;
    cout << "请输入姓名:";
    cin >> name;
    Node* node = new Node(num, name, NULL);
    if (m_head == NULL)
        m_head = m_tail = node;
    else{
        m_tail->m_next = node;
        m_tail = node;
    }
    ofstream ofs("a.txt",ios::app);
    ofs << node->m_num << ' ' << node->m_name << endl;
    ofs.close();
    cout << "已成功增加联系人!" << endl;
}
//显示全部联系人信息
void TongXun::list(){
    ifstream ifs("a.txt");
    if (! ifs){
        perror("打开文件失败!");
        return ;
    }
    m_head = m_tail = NULL;
    string s1, s2;
    while(ifs >> s1){
        //ifs.setf(ios::skipws);
        ifs >> s2;
        //ifs.setf(ios::skipws);
        Node* node = new Node(s1, s2);
        if(m_head == NULL)
            m_head = node;
        else
            m_tail->m_next = node;
        m_tail = node;
    }
    Node* next = m_head;
    cout << "通讯录中所有联系人信息如下: " << endl;
    for(; next;){
        cout << next->m_name << " : " << next->m_num<< endl;
        next = next->m_next;
    }
}
//查找联系人信息
void TongXun::look(){
    cout << "请输入你要查找的姓名: ";
    cin >> name;
    ifstream ifs("a.txt");
    m_head = m_tail = NULL;
    string s1, s2;
    while(ifs >> s1){
        ifs.setf(ios::skipws);
        ifs >> s2;
        ifs.setf(ios::skipws);
        Node* node = new Node(s1, s2);
        if(m_head == NULL)
            m_head = node;
        else
            m_tail->m_next = node;
        m_tail = node;
    }
    Node* node = m_head;
    for (; node;){
        if (name == node->m_name){
            cout << "你要查找的信息如下:" << endl;
            cout << node->m_name << " : "<< node->m_num << endl;
            return;
        }
    node = node->m_next;
    }
    cout << "你要查询的信息不存在!" << endl;
}
//修改联系人信息
void TongXun::change(){
    cout << "请输入你要修改的姓名: ";
    cin >> name;
    ifstream ifs("a.txt");
    m_head = m_tail = NULL;
    string s1, s2;
    while(ifs >> s1){
        ifs.setf(ios::skipws);
        ifs >> s2;
        ifs.setf(ios::skipws);
        Node* node = new Node(s1, s2);
        if(m_head == NULL)
            m_head = node;
        else
            m_tail->m_next = node;
        m_tail = node;
    }
    Node* node = m_head;
    for(;node;node = node->m_next){
        if(name == node->m_name){
            cout << "请输入新的电话号码:";
            cin >> num;
            node->m_num = num;
            cout << "修改成功!"<<endl;
            break;
        }
    }
    ofstream ofs("a.txt");
    node = m_head;
    for(;node;node = node->m_next)
        ofs << node->m_num << ' ' << node->m_name << endl;
    ofs.close();
}
//删除联系人
void TongXun::remove(){
    ifstream ifs("a.txt");
    m_head = m_tail = NULL;
    string s1, s2;
    while(ifs >> s1){
        ifs.setf(ios::skipws);
        ifs >> s2;
        ifs.setf(ios::skipws);
        Node* node = new Node(s1, s2);
        if(m_head == NULL)
            m_head = node;
        else
            m_tail->m_next = node;
        m_tail = node;
    }
    cout << "请输入你要删除的姓名: ";
    cin >> name;
    Node* node = m_head;
    Node* next = NULL;
    if(!m_head->m_next){
        if (name == m_head->m_name){
            node = m_head->m_next;
            delete m_head;
            m_head = node;
            cout << "删除成功!" << endl;
        }
    }
    else{
        if (name == m_head->m_name){
            node = m_head->m_next;
            delete m_head;
            m_head = node;
            cout << "删除成功!" << endl;
        }
        else{
            for(;node->m_next;node = node->m_next){
                if(name == node->m_next->m_name){
                    next = node->m_next->m_next;
                    delete node->m_next;
                    node->m_next = next;
                    cout << "删除成功!" << endl;
                    break;
                }
            }
        }
    }
    ofstream ofs("a.txt");
    node = m_head;
    for(;node;node = node->m_next)
        ofs << node->m_num << ' ' << node->m_name << endl;
    ofs.close();
}
