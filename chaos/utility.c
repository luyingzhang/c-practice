/*
 * utility.c
 *
 *  Created on: 2012/3/31
 *      Author: boris
 */

/**
 * 右邊補零
 * (範圍不超過 999位)
 * max: 欲回傳的長度
 * src: 字串陣列(含\0)
 */
char* padr0 ( int max, char src[] ){
	char *result ;
	result = (char*) malloc ( sizeof(char)*max );
	int i, null_i; //記錄從那一位開始要補零
	null_i = 999;
	for( i=0; i<max; i++ ){
		if( i > null_i ){
			result[ i ] = '0';
		}else{
			if( '\0' == src[i] ){
				null_i = i;
				result[ i ] = '0';
			}else{
				result[ i ] = src[i];
			}
		}
//		printf("\npadr0 result[i]: %c", result[i] );
	}
	return result;
}


