#include <stdio.h>
#include <string.h>

int main (void){

    char buf[32] = {0};
	FILE *fp = fopen("udc_info.txt", "r");
    int count = 0;
    
    if (fp){
        while(fscanf(fp, "%s", buf) != EOF){
            count ++;
            printf("buf is %s\n", buf);
            memset(buf, 0, sizeof (buf));
        }
        printf("%d\n", count);
        fclose(fp);
        fp = NULL;
    }
	return 0;
}
