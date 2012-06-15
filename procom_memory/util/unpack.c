#include <stdio.h>

char *unpack(unsigned char *hex, unsigned char *str, int sz )
{
   int  i = 0, j = 0, va ;

   while ( sz-- > 0 ) {
      if ( (va = *(str+j) >> 4) >= 10 )
         *(hex+i++) = va - 10 + 'A' ;
      else
         *(hex+i++) = va + '0' ;
      if ( (va = *(str+j++) & 0x0f) >= 10 )
         *(hex+i++) = va - 10 + 'A' ;
      else
         *(hex+i++) = va + '0' ;
   }
   return( (char *) hex ) ;
}
