#include <stdio.h>
#include <string.h>

int main (void){

    char buf[32] = {0};
	FILE *fp = fopen("udc_info.txt", "r");
    
    if (fp){
        while(1){
            fgets(buf, sizeof(buf), fp);

            if (feof(fp)){
                break;
            }

            if (buf[strlen(buf) - 1] == '\n'){
                buf[strlen(buf) - 1] = '\0';
            }
            printf("buf is %s\n", buf);
            memset(buf, 0, sizeof (buf));
        }
    }
	return 0;
}
