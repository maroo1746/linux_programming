#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[])
{
	struct student rec;
	char c;
	int id;
	FILE* fp;

	if (argc != 2) {
		fprintf(stderr, "how to use:%s filename\n", argv[0]);
		return 1;
	}

	if ((fp = fopen(argv[1], "rb+")) == NULL) {
		fprintf(stderr, "error : file not opened\n");
		return 2;
	}

	int n = 0;

	do {
		printf(" modify info : 1 | add info : 2 | quit : 3\n");
		printf("Enter the number\n");
		scanf("%d", &n);

		if (n == 1) {
			printf("Enter the student number to be modified: ");
			if (scanf("%d", &id) == 1) {
				fseek(fp, (id - START_ID) * sizeof(rec), SEEK_SET);
				if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
					printf("studentID: %8d name: %4s score: %4d\n", rec.id, rec.name, rec.score);
					printf("Enter new score: ");
					scanf("%d", &rec.score);
					fseek(fp, -sizeof(rec), SEEK_CUR);
					fwrite(&rec, sizeof(rec), 1, fp);
				}
				else printf("record %d does not exist\n", id);
			}
			else printf("input error\n");
		}

		if (n == 2) {
			printf("Enter the student number to be added: ");
			if (scanf("%d", &rec.id) == 1) {
				fseek(fp, (rec.id - START_ID) * sizeof(rec), SEEK_SET);
				
				if(fread(&rec, sizeof(rec), 1, fp) == 0) {
				
					printf("Enter name : ");
					scanf("%s", rec.name);
					printf("Enter score : ");
					scanf("%d", &rec.score);
				
					// fseek(fp, -sizeof(rec), SEEK_CUR); << the error point
					fwrite(&rec, sizeof(rec), 1, fp);
				} 
				else {
					printf("record %d already exist.\n", rec.id);
				}
			}
			else {
				printf("input error\n");
			}
		}
		fseek(fp, 0, SEEK_SET);

	} while (n != 3);

	fclose(fp);
	return 0;
}
