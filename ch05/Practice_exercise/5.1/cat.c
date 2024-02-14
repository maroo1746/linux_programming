#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd;
	int fd2;
	char buf[100];
	int n;

	if (argc == 1) {

		while ((n = read(0, buf, 100)) > 0) {
			write(1, buf, n);
		}

		return 0;
	}

	if (argc >= 2) {
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			perror("Error opening file");
			return 1;
		}
		while ((n = read(fd, buf, 100)) > 0) {
			write(1, buf, n);
		}
		close(fd);

		if (argc == 3) {
			fd2 = open(argv[2], O_RDONLY);
			if (fd2 == -1) {
				perror("Error opening second file");
				return 1;
			}
			while ((n = read(fd2, buf, 100)) > 0) {
				write(1, buf, n);
			}
			close(fd2);
		}
		return 0;
	}
}