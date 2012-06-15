#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/*--------------------------------------------------------------------------
 * Function ID:	GetSysDateTime
 * Description:	get current date and time
 * Parameters:	1). string buffer to save current datetime
 *		2). string buffer of format
 * Return:	none
 --------------------------------------------------------------------------*/
void GetSysDateTime(char *time_str, int str_len, char *time_fmt) {
	time_t bintime;

	time(&bintime);
	strftime(time_str, str_len, time_fmt, localtime(&bintime));
}

