#include <stdio.h>
typedef struct {
    char a[20];     //字符数组
    int price;
    int quantity;
}phone;
void read(phone *p_phone){
    printf("请输入品牌信息:");
    fgets(p_phone->a, 20, stdin);
    printf("请输入价格和数量信息:");
    scanf("%d %d",&(p_phone->price), &(p_phone->quantity));
    /*scanf("%*[^\n]");
    scanf("%*c");*/
    }
void print(phone *p_phone){
    printf("电话信息是%s, %d和%d\n", p_phone->a, p_phone->price, p_phone->quantity);
    }
int main(){
    phone phones[3];
    int loop = 0;
    for(loop = 0;loop <= 2;loop++)
        read(phones + loop);
    for(loop = 0;loop <= 2;loop++)
        print(phones + loop);
    return 0;
}
