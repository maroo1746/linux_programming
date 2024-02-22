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
int Deposit();
int Withdrawal();
int CheckBalance();

int main() {

	int n;
	char c;

	do {
		printf("What do you want to do? \n1. Create Account 2. Deposit 3. Withdrawal 4. Check Balance \nChoose the number : ");
		scanf("%d", &n);

		if (n == 1) {
			CreateAccount();
		}

		if (n == 2) {
			Deposit();
		}

		if (n == 3) {
			Withdrawal();
		}

		if (n == 4) {
			CheckBalance();
		}

		printf("Would you like to continue with the banking transaction? (Y/N) : ");
		getchar();
		scanf("%c", &c);

	} while (c == 'Y');
}

int CreateAccount() {

	int fd;
	struct account rec;

	if ((fd = open("accountDB.txt", O_RDWR | O_CREAT, 0600)) == -1) {
		perror("accountDB.txt");
		return 2;
	}

	printf("%-9s %-20s %-9s\n", "number", "name", "balance");
	while (scanf("%d %s %d", &rec.number, rec.name, &rec.balance) == 3) {
		
		lseek(fd, (rec.number - START_NUMB) * sizeof(rec), SEEK_SET);
		if (write(fd, &rec, sizeof(rec)) != sizeof(rec)) {
			perror("Failed to write to accountDB.txt");
			close(fd);
			return 3;
		}

	}

	close(fd);
	return 0;

}

int Deposit() {

	int fd;
	struct account rec;
	char buffer[100];
	int number;
	int deposit;
	int written;
	char c;

	if ((fd = open("accountDB.txt", O_RDWR | O_CREAT, 0600)) == -1) {
		perror("accountDB.txt");
		return 2;
	}

	do {
		printf("wirte down your account number : ");
		if (scanf("%d", &number) == 1) {
			lseek(fd, (number - START_NUMB) * sizeof(rec), SEEK_SET);
			if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.number != 0)) {
				printf("number : %d name : %s balance : %d\n", rec.number, rec.name, rec.balance);
				printf("Please enter the amount to deposit : ");
				scanf("%d", &deposit);
				rec.balance = rec.balance + deposit;
				int written = sprintf(buffer, "%d %s %d\n", rec.number, rec.name, rec.balance);

				lseek(fd, -sizeof(rec), SEEK_CUR);
				write(fd, &rec, sizeof(rec));
			}
			else {
				printf("there is no account for %d\n", number);
			}
		}
		else {
			printf("input error\n");
		}
		printf("do you want to continue? (Y/N) : ");
		getchar();
		scanf("%c", &c);

	} while (c == 'Y');

	close(fd);
	return 0;

}

int Withdrawal() {

	int fd;
	struct account rec;
	char buffer[100];
	int number;
	int withdrawal;
	int written;
	char c;

	if ((fd = open("accountDB.txt", O_RDWR | O_CREAT, 0600)) == -1) {
		perror("accountDB.txt");
		return 2;
	}

	do {
		printf("write down your account number : ");
		if (scanf("%d", &number) == 1) {
			lseek(fd, (number - START_NUMB) * sizeof(rec), SEEK_SET);
			if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.number != 0)) {
				printf("account number : %d name : %s balance : %d\n", rec.number, rec.name, rec.balance);
				printf("Please enter the amount to withdrawal : ");
				scanf("%d", &withdrawal);
				rec.balance = rec.balance - withdrawal;
				int written = sprintf(buffer, "%d %s %d\n", rec.number, rec.name, rec.balance);

				lseek(fd, -sizeof(rec), SEEK_CUR);
				write(fd, &rec, sizeof(rec));
			}
			else {
				printf("There is no account for %d\n", number);
			}
		}
		else {
			printf("input error\n");
		}
		printf("do you want to continue? (Y/N) : ");
		getchar();
		scanf("%c", &c);

	} while (c == 'Y');

	close(fd);
	return 0;
}

int CheckBalance() {

	int fd;
	struct account rec;
	char buffer[100];
	int number;
	int written;
	char c; 

	if ((fd = open("accountDB.txt", O_RDWR | O_CREAT, 0600)) == -1) {
		perror("accountDB.txt");
		return 2;
	}

	do {
		printf("write down your account number : ");
		if (scanf("%d", &number) == 1) {
			lseek(fd, (number - START_NUMB) * sizeof(rec), SEEK_SET);
			if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.number != 0)) {
				printf("account number : %d name : %s balance : %d\n", rec.number, rec.name, rec.balance);
			}
			else {
				printf("there is no account for %d\n", number);
			}
		}
		else {
			printf("input error\n");
			printf("do you want to continue? (Y/N) : ");
			getchar();
			scanf("%c", &c);
		}
	} while (c == 'Y');

	close(fd);
	return 0;
}


