#ifndef	_EZRFAPI_H
#define	_EZRFAPI_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 Input buffer format for FISC IC CARD COMMANDS(ALL ASCII STRING) :
 T1CMDCREATFILE	: FILE INFO
 T1CMDSELECT		: SelectType('P', 'D', 'E') + FILE ID(HEX CHAR[4])
 T1CMDLOCKDF 		: NULL
 T1CMDUNLOCKDF 	: DF ID(HEX CHAR[4])
 T1CMDREAD 		: ReadType('R','C','N','P','A') + RecNO(HEX CHAR[3])
 T1CMDWRITE 		: DATA to be written
 T1CMDWRITEwTAC 	: KeyID(HEX CHAR[2]) + TAC BLOCK
 T1CMDUPDATE 		: UpdateType('R', 'C', 'N', 'P') + RecNO(HEX(2))+DATA
 T1CMDERASEDF 	: NULL
 T1CMDBINARYADD 	: DATA to be ADDED
 T1CMDVERIFYPIN 	: PIN KEY ID(HEX CHAR[2]) + PIN VALUE
 T1CMDGENRANDOM 	: NULL
 T1CMDTERMAUTH 	: KEY ID(HEX CHAR[2]) + Encrypted DATA
 T1CMDUNLOCKKEYPIN 	: EF ID(HEX CHAR[4])
 T1CMDCARDAUTH 	: KEY ID(HEX CHAR[4]) + RAN NO R1 & R2
 T1CMDSETSESKEY 	: KEY ID(HEX CHAR[4]) + RAN NO R1
 T1CMDREADBINARY 	: NULL
 T1CMDUPDCIPHERREC 	: DATA
 */
#define	ERRT1CMD		-9501
#define	ERRT1SUBTYPE		-9502

#define	T1CMDSELECT 		1
#define	T1CMDREAD 		2
#define	T1CMDWRITE 		3
#define	T1CMDWRITEwTAC 		4
#define	T1CMDERASEDF 		5
#define	T1CMDLOCKDF 		6
#define	T1CMDGENRANDOM 		7
#define	T1CMDREADBINARY 	8
#define	T1CMDUNLOCKDF 		9
#define	T1CMDBINARYADD 		10
#define	T1CMDUNLOCKKEYPIN 	11
#define	T1CMDUPDCIPHERREC 	12
#define	T1CMDVERIFYPIN 		13
#define	T1CMDTERMAUTH 		14
#define	T1CMDCARDAUTH 		15
#define	T1CMDSETSESKEY 		16
#define	T1CMDUPDATE 		17
#define	T1CMDCREATFILE 		18

typedef struct { /* select command */
	char CmdTYPE; /* 'E', 'D', 'P' */
	char FID[0]; /* null terminated FID */
} SelBUF_t, *pSelBUF_t;

typedef struct { /* read command */
	char CmdTYPE; /* 'R', 'C', 'N', 'P', 'A' */
	char RecNO[3]; /* decimal rec number, for 'R' & 'A' */
} ReadBUF_t, *pReadBUF_t;

typedef struct { /* upadte command */
	char CmdTYPE; /* 'R', 'C', 'N', 'P' */
	char RecNO[2]; /* HEX rec number, for 'R', 16 - 0x10 */
	char DATA[0]; /* null terminated DATA */
} UpdateBUF_t, *pUpdateBUF_t;

typedef struct { /* PinVer, TermAuth, CardAuth, WRITEwTAC, SetSessionKEY */
	char KeyQ[2]; /* HEX PinQ/KeyQ number */
	char DATA[0]; /* null terminated DATA */
} CmnKeyBUF_t, *pCmnKeyBUF_t;

typedef struct { /* all other command */
	char DATA[4]; /* null terminated DATA */
} CmnDatBUF_t, *pCmnDatBUF_t;

typedef struct {
	char LEN[4];
	char DATA[0]; /* NULL Terminated */
} CmnBUF_t, *pCmnBUF_t;

typedef struct {
	char CMD[2]; /* command code */
	char SW[6]; /* command status sw */
	char OPT[8]; /* optional information */
} RETCMDSW_t, *pRETCMDSW_t;

#ifdef __cplusplus
}
#endif

#endif 	/* _EZRFAPI_H */
