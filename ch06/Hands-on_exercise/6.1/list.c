#include <sys/types.h> 
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>

void listDirectoriesRecursively(char* dir);
void printColored(const char* name, const struct stat* statbuf);

int main(int argc, char** argv) {

	char* dir;

	if (argc == 1)
		dir = ".";
	else dir = argv[1];

	listDirectoriesRecursively(dir);

}

void listDirectoriesRecursively(char* dir) {
	DIR* dp;
	struct dirent* d;
	char path[1000];
	struct stat path_stat;

	printf("\n");

	if ((dp = opendir(dir)) == NULL)  // 디렉토리 열기 
		perror(dir);

	printf("./%s: \n", dir);

	while ((d = readdir(dp)) != NULL) {

		// Skip the "." and ".." entries
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".git") == 0) {
			continue;
		}
		sprintf(path, "%s/%s", dir, d->d_name);
		
		stat(path, &path_stat);		
		printColored(d->d_name, &path_stat);
		
	}

	printf("\n");

	dp = opendir(dir);

	while ((d = readdir(dp)) != NULL) {

		// Skip the "." and ".." entries
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 || strcmp(d->d_name, ".git") == 0) {
			continue;
		}

		sprintf(path, "%s/%s", dir, d->d_name);

		// Check if the path is a directory before recursing
		stat(path, &path_stat);
		if (S_ISDIR(path_stat.st_mode)) {
			listDirectoriesRecursively(path);
		}

	}
	closedir(dp);

}

void printColored(const char* name, const struct stat* statbuf) {
	if (S_ISDIR(statbuf->st_mode)) {
		printf("\033[1;34m%s\033[0m ", name);
	} else if (statbuf->st_mode & S_IXUSR) {
		printf("\033[1;32m%s\033[0m ", name);
	} else {
		printf("%s ", name);
	}
}
