#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

	int fd;
	char command[1000];

	if (argc < 2) {
		fprintf(stderr, "how to use : %s filename \n", argv[0]);
	}

	fd = open(argv[1], O_WRONLY | O_CREAT, 0600);
	if (flock(fd, LOCK_EX) != 0) {
		printf("flock error\n");
		close(fd);
		exit(0);
	}
	
	sprintf(command, "vi %s", argv[1]);

	system(command);

	if (flock(fd, LOCK_UN) != 0) {
		perror("flock error\n");
		close(fd);
		exit(0);
	}

	close(fd);
	return 0;

}
