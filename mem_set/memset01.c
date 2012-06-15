#include <stdio.h>
#include <string.h>
 
/*
 * string.h 的函數 memset() 將某一記憶體區段的前 n 個字元全部設定為某一字元。
 * 以下程式將字串 s 全部設成 'n' 
 */
int main(void)
{
    char s[] = "congratulation";
     
    printf("%s\n", memset(s, 'n', 12));//因為12小於s的長度，所以印出14個'n'
    printf("%s\n", memset(s, 'n', 13));//因為13小於s的長度，所以印出14個'n'
    printf("%s\n", memset(s, 'n', 14));//因為14小於s的長度，所以印出14個'n'
    printf("%s\n", memset(s, 'n', 15));
    printf("%s 長度: %d\n", memset(s, 'n', sizeof(s)), sizeof(s));
     
    return 0;    
}
