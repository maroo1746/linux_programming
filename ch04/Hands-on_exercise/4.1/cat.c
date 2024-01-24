#include <stdio.h>
#include <string.h>

/*print the content of the textfile to stdout*/
int main(int argc, char *argv[])
{
	FILE *fp;
	int c;
	char * str_n = "-n";
	int option_n = 0;

	if (argc < 2) 
		fp = stdin;
	else if (argc == 2)
		fp = fopen(argv[1], "r");
	else if (argc == 3)
		fp = fopen(argv[2], "r");

	c = getc(fp);
	
	if (argc == 3) {
		if (strcmp(argv[1], str_n) == 0) {
			int line = 1;
			printf("%3d ", line);
			while (c != EOF) {
				putc(c, stdout);
				if (c==10) {
					line++;
					printf ("%3d ", line);
				}
				c = getc(fp);
			}
		}
					
	} else {
		while (c != EOF) {
			putc(c, stdout);
			c = getc(fp);
		}
	}
	fclose(fp);
	return 0;
}
