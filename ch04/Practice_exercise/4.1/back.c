#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int main(int argc, char* argv[]) {

	char c;
	char buffer[MAXLINE];
	FILE* fp;
	int position;

	if (argc != 2) {
		fprintf(stderr, "how to use: %s filename\n", argv[0]);
		return 1;
	}

	if ((fp = fopen(argv[1], "rb+")) == NULL) {
		fprintf(stderr, "file opening error\n");
		return 2;
	}

	fseek(fp, 0, SEEK_END);
	position = ftell(fp);
	
	//printf("%d", position);

	while (position > 0) {
		fseek(fp, --position, SEEK_SET);
		c = getc(fp);

		if (c == EOF) {
			fprintf(stderr, "Error reading file\n");
			fclose(fp);
			return 3;
		}

		if (c == '\n') {
			if (fgets(buffer, MAXLINE, fp) != NULL) {
				printf("%s", buffer);
			}		
		
		}

		if (position == 0) {
			fseek(fp, -1, SEEK_CUR);
			if (fgets(buffer, MAXLINE, fp) != NULL) {
				printf("%s", buffer);
			}	
		}
	}

	fclose(fp);
	return 0;

}
