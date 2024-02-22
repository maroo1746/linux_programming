#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static char buf[10]; 
static int size = sizeof(buf);
static int buf_index = 0;
static int buf_filled = 0;

int getchar_custom() {
	if (buf_index >= buf_filled) {
		buf_filled = read(STDIN_FILENO, buf, size);
		buf_index = 0;

		if (buf_filled <= 0) {
			if (buf_filled < 0) {
				perror("read failed");
			}
			return EOF;
		}
	}

	return (unsigned char)buf[buf_index++];
}







