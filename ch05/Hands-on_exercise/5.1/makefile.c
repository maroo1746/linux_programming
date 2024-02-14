#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){ 
	
	int fd = open("file.txt", O_WRONLY | O_CREAT, 0600);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	int i = 1;
	int len;
	char buf[50];

	while (i <= 1000) {
		len = sprintf(buf, "This is line %d.\n", i);
		if (write(fd, buf, len) == -1) {
			perror("write");
			close(fd);
			return 1;
		}
		i++;
	}

	close(fd);
}
