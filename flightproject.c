#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Ilyass Mohamed PRG255NIJ Winter 2021*/
typedef struct Seat {
	int id;
	char* firstname;
	char* lastname;
	char used;
} Seat;
void menu()
{
	printf("\t\t\tEcono-Airlines Menu\n");
	printf("\t\t\tBy: Ilyaas Mohamed\n");
	printf("a.\tDisplay ALL seat assignments (including Empty).\n");
	printf("b.\tShow ONLY a list of empty seats and show total of empty seats.\n");
	printf("c.\tSHOW ONLY the assigned seats with name of person and total assigned.\n");
	printf("d.\tAssign the customer to an empty seat.\n");
	printf("e.\tDelete ONE seat assignment.\n");
	printf("f.\tDelete ALL seat assignments.\n");
	printf("q.\tQuit program.\n\n\n");
}
void allseats(int* last, Seat* array[]) {
	system("cls");
	printf("\t\t\t\t\tSeating Arrangement\n\n");
	FILE* fp;
	int i;
	int id;
	char fname[20];
	char lname[20];
	char used;
	fp = fopen("db.txt", "r");
	int count = 0;
	printf("\tSeat #\t\tUsed\t\tLastname\t\tFirstname\n\n");
	for (i = 0; i < 12; i++) {
		fscanf(fp, "%d %c %s %s", &id, &used, lname, fname);
		if (used == 'n') count++;
		printf("\t%2d", id);
		printf("\t\t%c", used);
		printf("\t\t%s", lname);
		printf("\t\t\t%s\n", fname);
	}
	printf("\n\tThere are %d Empty Seats\n", count);
	fclose(fp);
}
void allempty(int* last, Seat* array[]) {
	system("cls");
	printf("\t\t\t\t\tSeating Arrangement\n\n");
	FILE* fp;
	int i;
	int id;
	char fname[20];
	char lname[20];
	char used;
	fp = fopen("db.txt", "r");
	int count = 0;
	printf("\tSeat #\t\tUsed\t\tLastname\t\tFirstname\n\n");
	for (i = 0; i < 12; i++) {
		fscanf(fp, "%d %c %s %s", &id, &used, lname, fname);
		if (used == 'n') count++;
		else continue;
		printf("\t%2d", id);
		printf("\t\t%c", used);
		printf("\t\t%s", lname);
		printf("\t\t\t%s\n", fname);
	}
	printf("\nThere are %d Empty Seats\n", count);
	fclose(fp);
}
void allused(int* last, Seat* array[]) {
	system("cls");
	printf("\t\t\t\t\tSeating Arrangement\n\n");
	FILE* fp;
	int i;
	int id;
	char fname[20];
	char lname[20];
	char used;
	fp = fopen("db.txt", "r");
	int count = 0;
	printf("\tSeat #\t\tUsed\t\tLastname\t\tFirstname\n\n");
	for (i = 0; i < 12; i++) {
		fscanf(fp, "%d %c %s %s", &id, &used, lname, fname);
		if (used == 'y') count++;
		else continue;
		printf("\t%2d", id);
		printf("\t\t%c", used);
		printf("\t\t%s", lname);
		printf("\t\t\t%s\n", fname);
	}
	printf("\nThere are %d ASSIGNED Seats\n", count);
	fclose(fp);
}
void giveseat(int* last, Seat* array[]) {
	system("cls");
	printf("\tAvailable seats\n\n");
	FILE* fp;
	int i, count = 0;
	int id[12];
	char used[12];
	char fname[12][20];
	char lname[12][20];
	fp = fopen("db.txt", "r");
	for (i = 0; i < 12; i++) {
		fscanf(fp, "%d %c %s %s", &id[i], &used[i], lname[i], fname[i]);
		if (used[i] == 'n') {
			printf("\t\t%d\n", id[i]);
			count++;
		}
	}
	fclose(fp);
	int idnum;
	printf("\tThere are %d Available Seat(s)\n", count);
	while (1) {
		printf("\tEnter the seat you would like(0 to exit) ? ");
		scanf("%d", &idnum);
		if (idnum == 0)
			return;
		if (idnum < 1 || idnum > 12) 
		{
				printf("\tinvalid seat selection\n");
			continue;
		}
		if (used[idnum - 1] == 'y') {
			printf("\tAlready in use\n");
			continue;
		}
		else break;
	}
	printf("\tEnter last name:\t");
	scanf("%s", lname[idnum - 1]);
	printf("\tEnter first name:\t");
	scanf("%s", fname[idnum - 1]);
	used[idnum - 1] = 'y';
	fp = fopen("db.txt", "w"); 
		for (i = 0; i < 12; i++) {
			fprintf(fp, "%d %c %s %s\n", id[i], used[i], lname[i], fname[i]);
		}
	fclose(fp);
}
void delone(int* last, Seat* array[]) {
	system("cls");
	printf("\tSeats that can be Deleted\n");
	printf("\tSeat #\t\tLastname\t\tFirstname\n");
	
	FILE* fp;
	int i;
	int id[12];
	char used[12];
	char fname[12][20];
	char lname[12][20];
	fp = fopen("db.txt", "r");
	for (i = 0; i < 12; i++) {
		fscanf(fp, "%d %c %s %s", &id[i], &used[i], lname[i], fname[i]);
		if (used[i] == 'y') {
			printf("\t%2d", id[i]);
			printf("\t\t%s", lname[i]);
			printf("\t\t\t%s\n", fname[i]);
		}
	}
	fclose(fp);
	int seatnum;
	while (1) {
		printf("\tchoose seat to delete(0 to quit)");
		scanf("%d", &seatnum);
		if (seatnum == 0) {
			return;
		}
		if (used[seatnum - 1] == 'n'); {
			printf("\tAleady Empty...Enter again\n");
				continue;
		}
		break;
	}
	used[seatnum - 1] = 'n';
	strcpy(lname[seatnum - 1], "EMPTY");
	strcpy(fname[seatnum - 1], "SEAT");
	fp = fopen("db.txt", "w");
	for (i = 0; i < 12; i++) {
		fprintf(fp, "%d %c %s %s\n", id[i], used[i], lname[i],
			fname[i]); 
	}
	fclose(fp);
}
void eraseall(int* last, Seat* array[]) {
	system("cls");
	char in[10];
	printf("\tDo you want to RESET the data?[y=yes..n=no] ");
	scanf("%s", in);
	char ch = in[0];
	int i;
	if (strlen(in) == 1 && (ch == 'y' || ch == 'Y')) {
		FILE* fp = fopen("db.txt", "w");
		for (i = 0; i < 12; i++) {
			fprintf(fp, "%d %c %s %s\n", i + 1, 'n', "EMPTY", "SEAT");
		}
		fclose(fp);
	}
}
int main() {
	printf("This is a flight seat reservation program, press any key to continue\n");
	system("pause");
	system("cls");
	char ch;
	int last = 0;
	Seat* array[12];
	char input[20];
	for (;;) {
			menu();
			printf("Enter your selection\n");
			scanf("%s", input);
			if (strlen(input) != 1) {
				printf("\tPlease enter valid label.");
				system("pause");
				system("cls");
			}
			ch = input[0];
			if (ch == 'a' || ch == 'A') {
				allseats(&last, array);
				system("pause");
				system("cls");
			}
			else if (ch == 'b' || ch == 'B') {
				allempty(&last, array);
				system("pause");
				system("cls");
			}
			else if (ch == 'c' || ch == 'C') {
				allused(&last, array);
				system("pause");
				system("cls");
			}
			else if (ch == 'd' || ch == 'D') {
				giveseat(&last, array);
				system("pause");
				system("cls");
			}
			else if (ch == 'e' || ch == 'E') {
				delone(&last, array);
				system("pause");
				system("cls");
			}
			else if (ch == 'f' || ch == 'F') {
				eraseall(&last, array);
				system("pause");
				system("cls");
			}
			else if (ch == 'q' || ch == 'Q') {
				system("pause");
				system("cls");
				return 0;
			}
			else {
				printf("\tPlease enter valid label.\n");
				continue;
			}
		}
		return 0;
	}

