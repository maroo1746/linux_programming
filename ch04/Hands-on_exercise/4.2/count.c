#include <stdio.h>
#include <string.h>

int option_l = 0;
int option_w = 0;
int option_c = 0;

void count_line (FILE* fp);
void count_word (FILE* fp);
void count_char (FILE* fp);
void count(FILE* fp);

int main(int argc, char *argv[])
{
	FILE *fp;

	if (argc < 2) {
		fp = stdin;	
		count(fp);		
		return 0;
	} 
	
	char * str_l = "-l";
	char * str_w = "-w";
	char * str_c = "-c";

	fp = fopen(argv[argc-1], "r");
	int i = 1;
	while (i+2 <= argc) {
		if (strcmp (argv[i], str_l) == 0) {
			option_l = 1;
		}
		if (strcmp (argv[i], str_w) == 0) {
			option_w = 1;
		}
		if (strcmp (argv[i], str_c) == 0) {
			option_c = 1;
		}
		i++;
	}
	
	if (option_l==0 && option_w==0 && option_c==0) {
		count_line(fp);
		count_word(fp);
		count_char(fp);
	} else {
		if (option_l == 1) {
			count_line(fp);
		}
		if (option_w == 1) {
                        count_word(fp);
                }
		if (option_c == 1) {
                        count_char(fp);
                }
	}
	fclose(fp);
}

void count(FILE* fp) {

	int character;
	int previous_character = 32;
	
	int count_char = 0;
	int count_word = 0;
	int count_line = 0;
	
	while ((character = getc(fp)) != EOF) {

		if (character == 10) {
			count_line++;
			if (previous_character != 32 && previous_character != 10) {
				count_word++;
			}
		}
		else if (character == 32) {
			if (previous_character != 32 && previous_character != 10) {
				count_word++;
			}
		}
		else {
			count_char++;
		}

		previous_character = character;
	}

	if (previous_character != 32 && previous_character != 10) {
		count_word++;
	}

	printf("%d characters\n", count_char);
	printf("%d words\n", count_word);
	printf("%d lines\n", count_line);

}

void count_line (FILE *fp) {
	
	fseek(fp, 0L, SEEK_SET);	
	
	char buffer[1000];
	int count = 0;
	while (fgets(buffer, 1000, fp) != NULL) {
		count++;
	}
	
	printf ("%d lines\n", count);
} 

void count_word (FILE *fp) {
	
	fseek(fp, 0L, SEEK_SET);
	
	int count = 0;
	int character;
	int previous_character = 32;

	while ((character = getc(fp)) != EOF) {

		if (character == 10) {
			if (previous_character != 32 && previous_character != 10) {
				count++;
			}
		}
		else if (character == 32) {
			if (previous_character != 32 && previous_character != 10) {
				count++;
			}
		}
		previous_character = character;
	
	}

	if (previous_character != 32 && previous_character != 10) {
		count++;
	}
	
	printf("%d words\n", count);
}

void count_char (FILE *fp) {
	
	fseek(fp, 0L, SEEK_SET);
	
	int count = 0;
	int c = getc(fp);
	while (c != EOF) {
		if (c != 32 && c != 10) {
			count++;
		}
		c = getc(fp);
	}

	printf("%d characters\n", count);
}

