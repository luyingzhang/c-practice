/*
 * main.c
 *
 *  Created on: 2012/3/28
 *      Author: boris
 */


int main(int argc, char** argv) {

	char count[7] = {'0','0','0','0','0','0','0'};
	sprintf( count,"%d", 12 );//將int轉char *
	int i;
	for( i=0; i<7; i++ ){
		if( '\0' == count[i] ){
			printf ( "\ncount 0: %d", count[i] );
		}else{
			printf ( "\ncount: %d", count[i] );
		}
	}
}



