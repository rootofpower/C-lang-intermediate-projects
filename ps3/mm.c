#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

int mighty_method(char*);

int main(int argc, char *argv[])
{
    char str[1000000] = {0};
    scanf("%s", str);
    printf("%d\n", mighty_method(str));
    
    return 0;
}

int mighty_method(char *str){
    if(str == NULL) return 0;
    if(strcmp(str, "") == 0) return 0;
    char sum[1000] = {0};
    int result = 0;
    for(int i = 0; *(str + i); i++){
        if(!isdigit(*(str + i))) return 0;
        result += *(str + i) - '0'; 
    }
    sprintf(sum, "%d", result);
    result = atoi(sum);
    if(result >= 10) result = mighty_method(sum);
    return result;
}
