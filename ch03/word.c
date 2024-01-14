#include <stdio.h>
#include "word.h"

void wc(char name[]) {

	int character;
	int previous_character = 32;

	FILE* fp = fopen(name, "r");

	int count_char = 0;
	int count_word = 0;
	int count_line = 0;

	while ((character = getc(fp)) != EOF) {

		if (character == 10) {
			count_line++;
			if (previous_character != 32 & previous_character != 10) {
				count_word++;
			}
		}
		else if (character == 32) {
			if (previous_character != 32 & previous_character != 10) {
				count_word++;
			}
		}
		else {
			count_char++;
		}

		previous_character = character;
	}

	if (previous_character != 32 & previous_character != 10) {
		count_word++;
	}

	printf("number of characters : %d\n", count_char);
	printf("number of words : %d\n", count_word);
	printf("number of lines : %d\n", count_line);
}
