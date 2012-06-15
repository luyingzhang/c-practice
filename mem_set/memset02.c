#include <stdio.h>
#include <string.h>
 
/*
 * 一般方法是用雙迴圈來設定二維陣列的值，
 * 這裡使用memset來設定陣列初值。
 * memset為字元填入的函式，整數由2或4個位元組(字元)組成
 * 設定的值是0x01，但存入的值卻是0x0101，而導致錯誤的答案。
 */
int main(void)
{
    int matrix[60][30];
    //memset( matrix, 1, sizeof(matrix) );//7200
    //printf("%d 長度: %d\n", matrix, sizeof(matrix));
    memset( matrix, 1, 1800 );
    printf("%d\n", matrix[0][0]);
    printf("%d\n", matrix[0][1]);
    printf("%d\n", matrix[1][1]);
     
    return 0;    
}
