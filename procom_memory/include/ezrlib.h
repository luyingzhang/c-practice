#ifndef	_EZRLIB_H
#define	_EZRLIB_H

#ifndef	__UCHAR_t__
#define	__UCHAR_t__
typedef unsigned char	uchar ;
#endif
#ifdef	__cplusplus
extern "C" {
#endif

#define	EZRTIMEOUT	-500
#define	EZRCMDFAIL	-501
#define	EZRINVSIZE	-502
#define	EZRCMDNAK	-503
#define	EZROUTSYN	-504
#define	EZROPENCOM	-505
#define	EZRPORTNOTOPEN	-506
#define	EZRWRITEERR	-507

int EzrInit( void ) ;
int EzrSCpresent( void ) ;
int EzrSCpowerUP( void ) ;
int EzrSCpowerDOWN( void ) ;
int EzrClosePORT( void ) ;
int EzrT0read ( uchar* sw, uchar* cmd, uchar* buf, int sz ) ;
int EzrT0write( uchar* sw, uchar* cmd, uchar* buf, int sz ) ;
int EzrT1cmdIO( char* sw, char* out, char* ins, char* buf, int sz, int le ) ;

int writeEZ100R( int mid, uchar *buf, int cnt ) ;
int readEZ100R( int cmd, uchar *buf ) ;

/*
int openEZ100R( char *szPort ) ;
int closeEZ100R( void ) ;
int WRITEnBYTES( uchar* pchBuffer, int cbBuffer) ;
int READnBYTES( uchar* buf, int n ) ;
*/
#define READnBYTES(a, b)  ReadBytesRS232(a, b)
#define WRITEnBYTES(a, b) SendBytesRS232(a, b)
#define closeEZ100R       ClosePortRS232
#define openEZ100R(a)     OpenPortRS232(a)

#ifdef	__cplusplus
}
#endif

#endif /* _EZRLIB_H */
