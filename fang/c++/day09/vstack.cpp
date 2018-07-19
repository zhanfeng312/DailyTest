#include <iostream>
#include <stdexcept>
using namespace std;
//基于顺序表的堆栈
class Stack{
    public:
        //构造函数中分配内存
        Stack(size_t size = 10): //缺省形参
            m_array(new int[size]), m_size(size),
            m_top(0){}
        //析构函数中释放内存
        ~Stack(void){
            if (m_array){
                delete[] m_array;
                m_array = NULL;
            }
        }
        //得到栈顶元素
        int top() {
            int temp = m_top - 1;
            if (-1 == temp)
                throw UnderFlow();
            return m_array[temp];
        }
        //圧入
        void push(int data){
            if (full())
                throw OverFlow(); //抛出异常
            m_array[m_top++] = data;
        }
        //弹出
        int pop (void){
            if (empty())
                throw UnderFlow();//抛出异常
            return m_array[--m_top];
        }
        //判满
        bool full(void) const{
            return m_top >= m_size;
        }
        //判空
        bool empty(void) const{
            return !m_top;
        }
    private:
        //上溢异常
       class OverFlow : public exception{
            const char* what(void) const throw(){
                return "堆栈上溢";
            }
        };
        //下溢异常
        class UnderFlow : public exception{
            //覆盖了what函数,运用多态知识,执行子类的what函数.
            const char* what(void) const throw(){
                return "堆栈下溢";
            }
        };
        int* m_array;    //数组
        size_t m_size;   //容量
        size_t m_top;    //栈顶
};
void printb(unsigned int numb, int base){
    Stack stack(256);//256  6 
    do {
        stack.push(numb % base);
    }
    while (numb /= base); //考虑0,为0不满足条件
    while (! stack.empty()){
        int digit = stack.pop();
        if (digit < 10)
            cout << digit;
        else
            cout << char(digit - 10 + 'A');
    }
    cout << endl;
}
int main (void){
    try{
        Stack stack;
        for (int i = 0; !stack.full(); ++i)
            stack.push(i);
        //stack.push(8);
        cout << "当前的栈顶元素为:" << stack.top() << endl;
        while (! stack.empty())
            cout << stack.pop()<< ' ';
        cout << endl;
        cout << "当前的栈顶元素为:" << stack.top() << endl;
    }
    catch(exception& ex){ //引用子类对象的基类引用,属于多态,调用子类的what()函数
        cout << ex.what() << endl;
        return -1;
    }
    cout << "输入一个整数:" << flush;
    int numb;
    cin >> numb;
    cout << "您想看几进制:"<< flush;
    int base;
    cin >> base;
    cout << "结果:";
    printb(numb, base);
    return 0;
}
