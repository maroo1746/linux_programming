#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
	char* std_buf;
	int size = 10;
	std_buf = (char*)malloc(sizeof(char) * size);
	if (std_buf == NULL) {
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	int bytes_read;
	int current_position = 0;

	while(1) {
		bytes_read = read(STDIN_FILENO, std_buf + current_position, size - current_position);

		// error check
		if (bytes_read < 0) {
			perror("read failed");
			free(std_buf);
			exit(EXIT_FAILURE);
		}

		// EOF check
		if (bytes_read == 0) {
			break;
		}
		
		if (bytes_read == size - current_position) {
			current_position = current_position + bytes_read;
			if (std_buf[current_position - 1] != '\n') {
				size = size * 2;
				char* temp_buf = realloc(std_buf, sizeof(char) * size);
				if (temp_buf == NULL) {
					perror("Failed to reallocate memory");
					free(std_buf);
					exit(EXIT_FAILURE);
				}
				std_buf = temp_buf;
			}
			else {
				break;
			}
		}
		else {
			current_position = current_position + bytes_read;
			break;
		}

	}

	for (int i = 0; i < current_position; i++) {
		printf("%c ", std_buf[i]);
	}
	printf("\n");

	free(std_buf);
	return 0;

}







