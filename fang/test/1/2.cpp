#include<iostream>
using namespace std;
void findman(int men[], int n)
{
    int flag = n;//men中为0的个数
    int k = 0;
    for(;;){
        if(flag == 1)//当0的个数为1时，退出循环
            break;
        for(int j = 0;j < n; j++){
            if(men[j] == 1)
                //如果men的值为1那么跳过此人，向下接着数。
                continue;
            k++;
            //men值为0的人开始报数
            k %= 3;
            //使k的值循环为1,2,0
            if(k == 0){
                men[j] = 1;
                //如果k得值为0则那么则是报数为3的人，则使其值为1，踢出报数范围
                flag--;
                //标志减
            }
        }
    }
}
int main(){
    int men[5] = {0};
    findman(men, 5);
    for(int i=0;i<5;i++){//找出值唯一为0的人
         if(men[i] == 0)
            cout << "最后退出的人的序号为:" << i <<endl;
    }
    return 0;
}
          
      
                    
        

