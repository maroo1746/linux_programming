#include <stdio.h>
#include "print.h"

char line[MAXLINE];

void printfile(char name[]) {

	FILE* fp = fopen(name, "r");

	while (fgets(line, MAXLINE, fp) != NULL) {
		printf("%s", line);
	}

	fclose(fp);

	return 0;

}

