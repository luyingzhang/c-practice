#include <stdio.h>
#include <stdlib.h>

int ntgetopt(int argc, char* argv[], char* OptStr, char* bol) {
	int i, j;

	for (i = 0; OptStr[i]; i++) {
		*(bol + i) = 0;
		for (j = 1; j < argc; j++) {
			if (argv[j][0] != '-')
				continue;
			if (argv[j][1] == OptStr[i]) {
				*(bol + i) = -1;
				if ((j + 1) < argc) {
					if (argv[j + 1][0] != '-')
						*(bol + i) = j + 1;
				}
				break;
			}
		}
	}
	for (i = 1; i < argc && argv[i][0] == '-'; i++)
		;
	return (i);
}
