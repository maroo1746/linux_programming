#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "getchar.h"

int main() {
	
	char str[100];
	int ch, i = 0;
	printf("Enter a string: ");
	
	fflush(stdout);
	
	while ((ch = getchar_custom()) != '\n' && i < 99) {
		str[i++] = ch;
	}
	
	str[i] = '\0'; 
	printf("You entered: %s\n", str);
	return 0;
	
}
