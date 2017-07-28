#include <stdio.h>
#include <stdlib.h>
void split(char *p_str, char **pp_str) {
    char *p_result;
    int pos = 0;        //记录下标
    while((',' != *(p_str + pos)) && (0 != *(p_str + pos))){
        pos++;
    }
    pos++;
    p_result = (char *)malloc(pos * sizeof(char));
    if(p_result){
        pos = 0;
        while((',' != *(p_str + pos)) && (0 != *(p_str + pos))) {
            *(p_result + pos) = *(p_str + pos);
            pos++;
        }
        *(p_result + pos) = 0;
    }
        *pp_str = p_result;
}
int main(){
    char *ptr = NULL;
    char a[30] = "abcdef,haung,fang";
    split(a, &ptr);
    printf("%s\n",ptr);
    free(ptr);
    ptr = NULL;
    return 0;
}
