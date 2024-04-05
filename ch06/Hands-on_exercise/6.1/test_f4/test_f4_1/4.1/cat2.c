#include <stdio.h>
#include <string.h>

void cat_basic(FILE *fp);
void cat_option_n(FILE *fp);

/*print the content of the textfile to stdout*/
int main(int argc, char *argv[])
{
	FILE *fp;

	if (argc < 2) {
		fp = stdin;
		cat_basic(fp);
		return 0;
	} 
	
	char * str_n = "-n";
	int option_n = 0;
	
	fp = fopen(argv[argc-1], "r");
	
	int i = 1;
	while (i+2 <= argc) {

		if (strcmp(argv[i], str_n) == 0) {
			option_n = 1;
		}
		i++;

	}
	
	if (option_n == 1) {
		cat_option_n(fp);
		return 0;
	}
	
	cat_basic(fp);
}

void cat_basic(FILE *fp) {
	
	int c;
	
	while ((c = getc(fp)) != EOF) {
		putc(c, stdout); 
	}
	fclose(fp);
	
}

void cat_option_n(FILE *fp) {

	int c;
	int line = 1;
	
	printf("%3d ",line);
	while ((c = getc(fp)) != EOF) {
		putc(c, stdout); 
		if (c==10) {
			line++;
			printf("%3d ", line);
		}
	}
	
	fclose(fp);	
}
