#ifndef	_USBAPI_H
#define	_USBAPI_H
#include <stdcall.h>

#ifdef	__cplusplus
extern "C" {
#endif
#ifndef __UCHAR_t__
#define __UCHAR_t__
typedef unsigned char uchar ;
#endif

int STDCALL ApiPRESENTcard( char* port, int tmv ) ;
int STDCALL ApiCLOSEcard( void ) ;
int STDCALL ApiREMOVEcard( int tmv ) ; /* wait time out value */
int ApiT1cmdIO(char* sw, char* out, char* ins, char* buf, int lc, int le) ;
int ApiVerifyPIN( char* sw, char* pin ) ;
int ApiModifyPIN( char* sw, char* pin ) ;
int ApiReadDATA(char* sw, char *out, char* ef, char* r_no, int sz) ;
int ApiRewriteDATA(char* sw, char *in, char* ef, char* r_no, int sz) ;

#ifdef	__cplusplus
}
#endif

#endif 	/* _USBAPI_H */
