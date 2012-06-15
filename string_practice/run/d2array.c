#include <stdio.h>
#include <string.h>

/**
 * 搜尋字串陣列中符合的字串
 */

static int binsearch(char *str[], int max, char *value);

int main(void) {
	/* note, array needs to be sorted for bsearch... */
	char *strings[] = { "bill", "chris", "jason", "randy", "trish" };
	int i, asize, result;

	i = asize = result = 0;

	asize = sizeof(strings) / sizeof(strings[0]);

	for (i = 0; i < asize; i++)
		printf("%d: %s\n", i, strings[i]);

	printf("\n");

	if ((result = binsearch(strings, asize, "randy")) != 0)
		printf("`randy' found at position: %d\n", result);
	else
		printf("`randy' NOT found..\n");

	if ((result = binsearch(strings, asize, "nick")) != 0)
		printf("`nick' found at %d\n", result);
	else
		printf("`nick' was NOT found..\n");

	return 0;
}

static int binsearch(char *str[], int max, char *value) {
	int position;
	int begin = 0;
	int end = max - 1;
	int cond = 0;

	while (begin <= end) {
		position = (begin + end) / 2;
		if ((cond = strcmp(str[position], value)) == 0)
			return position;
		else if (cond < 0)
			begin = position + 1;
		else
			end = position - 1;
	}

	return 0;
}
