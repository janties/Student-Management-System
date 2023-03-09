#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    char name[20];
	char surName[20];
    char id[20];
	char departmant[30];
	char gender[10];
	char birthPlace[20];
	char age[5];
    char phone[20];
}Student;

void printTableHeader()
{
	system("cls");
    printf("+-----------+-----------+-------------------+---------------------------+----------+---------+----------------+--------------+\n");
    printf("|    Ad     |   Soyad   |         No        |           Bolum           | Cinsiyet |   Yas   |   Dogum Yeri   |  Telefon     |\n");
    printf("+-----------+-----------+-------------------+---------------------------+----------+---------+----------------+--------------+\n");
}

void printStudent(Student k) {
    printf("%10s%11s%19s%28s%12s%10s%15s%15s\n", k.name, k.surName, k.id, k.departmant, k.gender, k.age, k.birthPlace, k.phone);
}

Student readStudentFromInput() {
    Student k;
    printf("\nAd: ");
    scanf("%s",k.name);
    printf("Soyad: ");
    scanf("%s",k.surName);
    printf("Ogrenci No: ");
    scanf("%s",k.id);
    printf("Bolum: ");
    scanf("%s",k.departmant);
    printf("Cinsiyet: ");
    scanf("%s",k.gender);
    printf("DogumYeri: ");
    scanf("%s",k.birthPlace);
    printf("Yas: ");
    scanf("%s",k.age);
    printf("Telefon: ");
    scanf("%s",k.phone);
    return k;
}
//main menu
void display()
{
	printf("\nMENU\n*********************\n");
	printf("1-Kayit Ekle\n");
	printf("2-Kayitlari Listele\n");
	printf("3-Kayit Ara\n");
	printf("4-Kayit Duzenleme\n");
	printf("5-Cikis\n");
}
//ask for continue loop
void ask()
{
	printf("\n\n =>  Devam etmek icin tuslama yapiniz...");
	getch();
	system("cls");
}
//case1============
void AddNewStudent()
{
	Student k = readStudentFromInput();
	FILE *db = fopen("students.dat", "a");
	fprintf(db, "%s,%s,%s,%s,%s,%s,%s,%s\n",k.name,k.surName,k.id,k.departmant,k.gender, k.age, k.birthPlace, k.phone);
	fclose(db);
}
//case2============
void ShowList() {
    FILE *db = fopen("students.dat", "r");
    if (db == NULL) {
        printf("Henuz hicbir kayit bulunmamakta!\n");//Dosya acilamadi.
        return;
    }
    Student k;
	printTableHeader();
    while (fscanf(db, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]\n", k.name, k.surName, k.id, k.departmant, k.gender, k.age, k.birthPlace, k.phone) == 8) {
        printStudent(k);
    }
    printf("\n");
    fclose(db);
}
//case3============
void edit(int line)
{
	Student k = readStudentFromInput();
    FILE *db = fopen("students.dat", "r");
    FILE *temp = fopen("temp.dat", "w");
    char lineBuffer[100];
    int currentLine = 1;
    while (fgets(lineBuffer, sizeof(lineBuffer), db)) {
        if (currentLine == line) {
            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s\n", k.name, k.surName, k.id, k.departmant, k.gender, k.age, k.birthPlace, k.phone);
        } else {
            fputs(lineBuffer, temp);
        }
        currentLine++;
    }
    fclose(db);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");// dosyanin adini degistir
}
//case4============
int SearchList()
{
	char keyword[20];
	int lineCtr = 1;
	printf("Ogrenci No Giriniz: ");
	scanf("%s", keyword);
	system("cls");//clear screen
    FILE *db = fopen("students.dat", "r");
    if (db == NULL) {
        printf("Dosya acilamadi.\n");
        return 0;
    }
    Student k;
    while (fscanf(db, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]\n", k.name, k.surName, k.id, k.departmant, k.gender, k.age, k.birthPlace, k.phone) == 8)
	{
        if (!strcmp(k.id, keyword))
		{
			printf("Kayit Bulundu!\n");
			printTableHeader();
			printStudent(k);
			fclose(db);
			return lineCtr;
        }
		lineCtr++;
    }
	printf("\nBulunamadi!\n\n");
    fclose(db);
	return 0;
}

int main()
{
	char c = ' ';
	int input;
	int listNumber = 0;
	int exit = 0;
	while (!exit)
	{
		display();
		scanf("%d", &input);
		system("cls");
		switch (input) {
			case 1:
				AddNewStudent();
				ask();
				break;
			case 2:
				ShowList();
				ask();
				break;
			case 3:
				SearchList();
				ask();
				break;
			case 4:
				listNumber = SearchList();
				if(listNumber)
					edit(listNumber);
				ask();
				break;
			case 5:
				exit = 1;
				break;
			default :
				printf("\nHatali tuslama!\n");
				ask();
			}
	}
	return 0;
}

