//Lab Sheet 1 Solution
#include <stdio.h>
#include <stdlib.h>

//#define TESTING_PHASE

#ifdef TESTING_PHASE
//Random data testing functions
static int initialized = 0;
int randInt() {
	if (!initialized) {
		srand(time(NULL));
		initialized = 1;
	}
	return rand();
}

void randStr(char* str, int len) {

	if (!initialized) {
		srand(time(NULL));
		initialized = 1;
	}
	for (int i = 0; i < len; i++) {
		str[i] = rand() % ('z' - 'A') + 'A';
	}
	str[len] = '\0';
}
#include <string.h>
void customScanf(const char* str, void * ptr) {
	if (strcmp(str, "%s") == 0) {
		int ran = randInt() % 15 + 4;
		randStr(ptr, ran);
		printf("%s\n", (char *)ptr);
	}
	else if (strcmp(str, "%f") == 0) {
		*(float*)(ptr) = randInt()%5000 + 1.0 / (randInt()%100 + 1);
		printf("%f\n", *(float*)(ptr));
	}
	else if (strcmp(str, "%d") == 0) {
		*(int*)(ptr) = randInt() * (randInt() % 2 * 2 - 1);
		printf("%d\n", *(int*)(ptr));
	}
	else if (strcmp(str, "%u") == 0) {
		*(unsigned int*)(ptr) = randInt() % 10;
		printf("%u\n", *(unsigned int*)(ptr));
	}
	else {
		scanf(str, ptr);
	}
}

#define scanf(a, b) customScanf(a, b)
#endif

//Excersice 1 : To calculate and display expenditure in taular form
#include <stdio.h>

//A string of months
const char* Months[] = {
	"Jan","Feb","March","April","May","June","July","Aug","Sept","Oct","Nov","Dec"
};

int ex1() {
	//2 float columns for sum and average values of the year
	float expenditures[100][14], totalSum = 0.;
	int beginYear = 0, nYears = 0,i = 0,j = 0;
	
	printf("Enter the number of years whose data are to be calculated : \t");
	scanf("%u", &nYears);
	beginYear = 2022 - nYears + 1;
	
	printf("Enter the monthly expenditures of each required years : \n");
	for (i = 0; i < nYears; i++) {
		printf("Year %d : \n", beginYear + i);
		for (j = 0; j < 12; j++) {
			printf("%s : ", Months[j]);
			scanf("%f", &expenditures[i][j]);
		}
	}

	//Calculating average expenditures
	for (i = 0; i < nYears; i++) {
		expenditures[i][12] = 0.0;
		for (j = 0; j < 12; j++) {
			expenditures[i][12] += expenditures[i][j];
		}
		totalSum += expenditures[i][12];
		expenditures[i][12] /= 12.0;
	}

	//Printing the values in tabular form:
	printf("Year\t");
	for (i = 0; i < 12; i++)
		printf("%s\t", Months[i]);
	printf("Average \n");

	for (i = 0; i < nYears; i++) {
		printf("\n%d", beginYear + i);
		for (j = 0; j < 13; j++) {
			printf("\t%.2f", expenditures[i][j]);
		}
	}
	printf("\nAverage monthly expenditure over all years = %.2f\
			\nAverage annual expenditure = % .2f\n", totalSum / (nYears * 12), totalSum / nYears);


	return 0;
}

//Excercise 2 : To find the position of a particular character in a given string
#include<stdio.h>

int ex2() {
	
	//Given string 
	const char* नाम = "idea without execution is worthless";
	//Tracking pointer
	char* सूचक = नाम;
	//Required letter
	char अक्षर = 'c';

	while (*सूचक != '\0') {
		if (*सूचक == अक्षर)
			break;
		सूचक++;
	}

	if (*सूचक == '\0')
		printf("The required letter %c could not be found in given string.\n", अक्षर);
	else
		printf("The letter %c is at %d from start of given string.\n", अक्षर, (int)(सूचक - नाम + 1));
	return 0;
}

//Excercise 3: Demonstration of use of structure in data management
#include <stdio.h>

struct Student {
	char name[100];
	int c_marks;
};

int ex3() {
	unsigned int nStudents = 0;
	struct Student students[100];
	int i = 0;
	printf("Enter the number of students whose data is to be stored : ");
	scanf("%u", &nStudents);

	for (i = 0; i < nStudents; i++) {
		printf("Enter the name of student %d : ", i + 1);
		scanf("%s", students[i].name);
		printf("Marks of %s in C programming : ", students[i].name);
		scanf("%d", &students[i].c_marks);		
	}

	printf("Now printing the student details :\n");
	printf("Name of Student\tMarks in C \n");
	for (i = 0; i < nStudents; i++) {
		printf("%s\t%d\n", students[i].name, students[i].c_marks);
	}

	return 0;
}

//Excercise 4: Recalling file i/o in C programming language using file pointers
#include <stdio.h>
#include <string.h>

typedef struct {
	char name[50];
	char address[100];
	unsigned int roll;
	char phone_no[50];
} Student;

void readFromFile(const char* fName) {
	FILE* fptr;
	Student students[50], temp;
	unsigned int nStudents = 0;
	int i = 0, j = 0;

	fptr = fopen(fName, "rb");
	if (!fptr) {
		fprintf(stderr, "Error in opening file %s for reading.\n", fName);
		return;
	}

	fseek(fptr, 0L, SEEK_END);
	nStudents = ftell(fptr) / sizeof(Student);
	fseek(fptr, 0L, SEEK_SET);

	fread(students, sizeof(Student), nStudents, fptr);

	//Sorting alphabetically
	for (i = 0; i < nStudents; i++) {
		for (j = i + 1; j < nStudents; j++) {
			if (strcmp(students[j].name, students[i].name) < 0) {
				temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
		}
	}

	//Printing the information
	printf("Roll \t Name of Student\tAddress\t\tPhone Number\n");
	for (i = 0; i < nStudents; i++) {
		printf("%u\t%s\t%s\t%s\n", students[i].roll, students[i].name, students[i].address, students[i].phone_no);
	}

	fclose(fptr);
}

void writeToFile(const char* fName) {
	FILE* fptr;
	Student students[50], temp;
	unsigned int nStudents = 0;
	int i = 0;

	fptr = fopen(fName, "wb");
	if (!fptr) {
		fprintf(stderr,"Error in opening file for writing.\n");
		return;
	}

	printf("Enter the number of students whose data is to be entered : ");
	scanf(" %u", &nStudents);

	printf("Enter the data of students : \n");
	for (i = 0; i < nStudents; i++) {
		printf("Name : ");
		scanf("%s", students[i].name);
		printf("Roll No : ");
		scanf("%u", &students[i].roll);
		printf("Address : ");
		scanf("%s", students[i].address);
		printf("Phone No : ");
		scanf("%s", students[i].phone_no);
	}

	fwrite(students, sizeof(Student), nStudents, fptr);

	fclose(fptr);

}

int ex4() {
	char choice = 'w';
	const char* fileName = "students.dat";
	printf("Enter character r to read from file, any other to write to file : ");
	scanf(" %c", &choice);

	if (choice == 'r')
		readFromFile(fileName);
	else
		writeToFile(fileName);

	return 0;
}

int main()
{
	ex1();
	system("pause");
	putchar('\n');
	ex2();
	system("pause");
	putchar('\n');
	ex3();
	system("pause");
	putchar('\n');
	ex4();
	system("pause");
	putchar('\n');
	return 0;
}