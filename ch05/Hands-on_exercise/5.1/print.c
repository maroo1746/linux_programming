#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int printLine(char* input, int* numb, char* filename);
int intPow(int base, int exp);

int main(int argc, char* argv[]) {

	int numb[1000] = { 0, };
	char input[1000];

	//new line
	if (argc != 2) {
		fprintf(stderr, "how to use: %s filename\n", argv[0]);
		return 1; 
	}

	printf("Enter the range: ");
	fgets(input, sizeof(input), stdin);

	int* line_numb;

	printLine(input, numb, argv[1]);

}

int printLine(char* input, int* numb, char* filename) {

	int n = 3;
	int* comma_position = (int*)malloc(sizeof(int) * n);
	int i = 0;
	int comma_n = 0;

	while (input[i] != '\0') {

		if (input[i] == ',' || input[i] == '\n') {

			if (comma_n >= n) {
				n = n * 2;
				comma_position = (int*)realloc(comma_position, sizeof(int) * n);
			}

			comma_position[comma_n] = i;
			comma_n++;
		}
		i++;
	}

	/*
	int a = 0;

	while (a < j) {
		printf("%d ", comma_position[a]);
		a++;
	}*/

	int n_ptr = comma_n;
	char** ptr;

	ptr = (char**)malloc(sizeof(char*) * n_ptr);
	if (ptr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return 1;
	}

	for (int b = 0; b < n_ptr; b++) {
		ptr[b] = (char*)malloc(100 * sizeof(char));
		if (ptr[b] == NULL) {
			fprintf(stderr, "Memory allocation for string %d failed\n", b);

			for (int c = 0; c < b; c++) {
				free(ptr[c]);
			}
			free(ptr);
			return 1;
		}
	}


	int start = 0;
	int end = 0;

	for (int d = 0; d < comma_n; d++) {

		if (d == 0) {
			end = comma_position[d];
		}
		else {
			start = comma_position[d - 1] + 1;
			end = comma_position[d];
		}

		int p = 0;
		while (start < end) {
			ptr[d][p++] = input[start++];
		}
		ptr[d][p] = '\0';
	}

	/*
	for (int e = 0; e < comma_n; e++) {
		printf("%s\n", ptr[e]);
	}
	*/

	int line_numb_current = 0;

	int line_numb_size = 10;

	int* line_numb = (int*)malloc(sizeof(int) * line_numb_size);

	int l = 0;

	for (int g = 0; g < comma_n; g++) {
		int ptr_len = strlen(ptr[g]);
		int slash_position = 0;

		for (int h = 0; h < ptr_len; h++) {
			if (ptr[g][h] == '-') {
				slash_position = h;
			}
		}

		int digit1[100] = { 0, };
		int digit2[100] = { 0, };
		int result = 0;
		int result1 = 0;
		int result2 = 0;

		if (slash_position == 0) {

			for (l = 0; l < ptr_len; l++) {

				if (ptr[g][l] != ' ') {
					digit1[l] = ptr[g][l] - '0';
					result += digit1[l] * intPow(10, (ptr_len - l - 1));
				}

			}

			if (line_numb_current == line_numb_size) {
				line_numb_size = line_numb_size * 2;
				line_numb = (int*)realloc(line_numb, sizeof(int) * line_numb_size);
			}

			line_numb[line_numb_current] = result;
			line_numb_current++;
			result = 0;

		}
		else {

			for (l = 0; l < slash_position; l++) {
				
				if (ptr[g][l] != ' ') {
					digit1[l] = ptr[g][l] - '0';
					result1 += digit1[l] * intPow(10, (slash_position - 1 - l));
				}

			}

			for (l = slash_position + 1; l < ptr_len; l++) {
				if (ptr[g][l] != ' ') {
					digit2[l] = ptr[g][l] - '0';
					result2 += digit2[l] * intPow(10, (ptr_len - l - 1));
				}
			}

			for (l = 0; l < (result2 - result1) + 1; l++) {

				if (line_numb_current == line_numb_size) {
					line_numb_size = line_numb_size * 2;
					line_numb = (int*)realloc(line_numb, sizeof(int) * line_numb_size);
				}

				line_numb[line_numb_current] = result1 + l;
				line_numb_current++;
			}

		}
	}
	/*
	for (l = 0; l < line_numb_current; l++) {
		printf("%d ", line_numb[l]);
	}
	*/
	for (int f = 0; f < n_ptr; f++) {
		free(ptr[f]);
	}
	free(ptr);

	free(comma_position);

	// Now open the file and print it. 

	FILE* fp;
	char buffer[1000];
	int count = 1;
	l = 0;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "file open error");
		return 2;
	};

	while (l <= line_numb_current) {
		
		fgets(buffer, 1000, fp);
		if (line_numb[l] == count) {
			printf("%3d : %s", line_numb[l], buffer);
			l++;
		}
		count++;
	}

	fclose(fp);

	free(line_numb);

	return 0;

}

int intPow(int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}
