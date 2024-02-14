#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int START_NUMB = 000001;

struct account {
	int number;
	char name[20];
	int balance;
};

int CreateAccount();

int main() {

	int n;

	printf("What do you want to do? \n1. Create Account 2. Deposit 3. Withdrawal 4. Check Balance \nChoose the number : ");
	scanf("%d", &n);

	if (n == 1) {
		CreateAccount();
	}

}

int CreateAccount() {

	int fd;
	struct account rec;
	char buffer[100];

	if ((fd = open("accountDB.txt", O_RDWR | O_CREAT, 0600)) == -1) {
		perror("accountDB.txt");
		exit(2);
	}

	printf("%-9s %-20s %-9s\n", "number", "name", "balance");
	while (scanf("%d %s %d", &rec.number, rec.name, &rec.balance) == 3) {
		int written = sprintf(buffer, "%d %s %d\n", rec.number, rec.name, rec.balance);
		
		lseek(fd, (rec.number - START_NUMB) * sizeof(rec), SEEK_SET);
		write(fd, buffer, written);

	}

	close(fd);
	exit(0);

}
