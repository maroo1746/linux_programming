#include <sys/types.h> 
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int printDiskUsageRecursively(char* dir);

int main(int argc, char** argv) {

	char* dir;

	if (argc == 1)
		dir = ".";
	else dir = argv[1];

	printDiskUsageRecursively(dir);	

}

int printDiskUsageRecursively(char* dir) {

	DIR* dp;
	struct dirent* d;
	char path[1024];
	struct stat path_stat;

	stat(dir, &path_stat);
	int current_dir_size = path_stat.st_size;
	double dir_size_kb = 0;
	
	if ((dp = opendir(dir)) == NULL)
		perror(dir);

	while ((d = readdir(dp)) != NULL) {
		// Skip the "." and ".." entries
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 ) {
			continue;
		}

		sprintf(path, "%s/%s", dir, d->d_name);

		if (stat(path, &path_stat) == -1) {
			perror("stat");
			continue;
		}

		if (S_ISDIR(path_stat.st_mode)) {
			current_dir_size += printDiskUsageRecursively(path);
		}
		else {
			current_dir_size += path_stat.st_size;
		}
	}
	
	closedir(dp);
	
	dir_size_kb = current_dir_size / 1024.0;
	printf("%.2f\t%s\n", dir_size_kb, dir);
	
	return current_dir_size;

}
