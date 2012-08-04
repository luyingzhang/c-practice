/*
 * start.c
 *
 *  Created on: 2012/8/4
 *      Author: boris
 */

/* Return 1 if c is part of string s; 0 otherwise */
int is_in(char *s, char c)
{
  while(*s){
	printf( "s=%d, *s=%c\n", s, *s );
    if(*s==c){
		printf( "%c is %c", c, *s );
    	return 1;
    }else{ s++; }
  }
  return 0;
}

int main(void){
	char *s = "i am rock";
	char c = 'a';
	is_in ( s, c );
	return 1;
}
