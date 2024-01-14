#include <stdio.h>
#include <string.h>
#include "print.h"
#include "word.h"

char name[100];

int main() {

	printf("your file's name : ");
	scanf("%s", name);

	//getchar();

	printfile(name);
	
	wc(name);

	return 0;

}
