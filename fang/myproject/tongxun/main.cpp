#include "tongxun.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
//函数的声明
void menu1();
void menu2();
void func();
void save();
typedef struct{
    string name;
    string mima;
}M;
void zhuce()
{
    M m;
    cout << "请输入用户名:";
    cin >> m.name;
    cout << "请输入密码:";
    cin >> m.mima;
    ifstream ifs("message.txt");
    string s1, s2;
    while(ifs >> s1){
        ifs.setf(ios::skipws);
        ifs >> s2;
        ifs.setf(ios::skipws);
        if (s1 == m.name && s2 == m.mima){
            cout << "该用户已经注册过,请直接登陆!"<< endl;
            return;
        }
    }
    ifs.close();
    ofstream ofs("message.txt", ios::app);
    ofs << m.name << ' '<< m.mima << endl;
    ofs.close();
}
void login()
{
    string name;
    string mima;
    cout << "请输入登陆名:";
    cin >> name;
    cout << "请输入密码:";
    cin >> mima;
    ifstream ifs("message.txt");
    string s1, s2;
    while(ifs >> s1){
        ifs.setf(ios::skipws);
        ifs >> s2;
        ifs.setf(ios::skipws);
        if (s1 == name && s2 == mima){
            cout << "*********欢迎登陆************"<< endl;
            func();
            return;
        }
    }
    cout << "登陆失败,请先注册后再登陆!" << endl;
}
void menu1(){
    cout << "*****************************" << endl;
    cout << "请选择你要进行的操作:        " << endl;
    cout << "1.注册  2.登陆 3.退出        " << endl;
    cout << "*****************************" << endl;
}
void menu2(){
    cout << "*****************************"<< endl;
    cout << "请选择你要进行的操作:        "<<endl;
    cout << "1.增加        2.查找         "<< endl;
    cout << "3.删除        4.修改         "<< endl;
    cout << "5.显示        6.退出         "<< endl;
    cout << "*****************************"<< endl;
}
void func()
{
    TongXun t;
    int number;
    while(1){
        menu2();
        cout << "请选择你要进行的操作类型:" << endl;
        cin >> number;
        switch(number){
            case 1:
                t.add();
                break;
            case 2:
                t.look();
                break;
            case 3:
                t.remove();
                break;
            case 4:
                t.change();
                break;
            case 5:
                t.list();
                break;
            case 6:
                cout << "欢迎下次登陆!" << endl;
                return;
            default:
                cout << "你进行的选择有误,请重新选择"<< endl;
                break;
        }
    }
}
int main(void){
    int number;
    while(1){
        menu1();
        cin >> number;
        switch(number){
            case 1:
                zhuce();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "Bye Bye" << endl;
                exit(0);
            default:
                cout << "您输入的选择有误,请重新选择!" << endl;
                break;
        }
    }
    return 0;
}
