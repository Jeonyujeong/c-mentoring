#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void signUp();
void logIn();
void Freedata();

typedef struct stNode{
	struct stNode* next;
	char stnum[20];
	char passward[20];
	char name[20];
	char lend;
}student;

student* head;
student* tail;
student* member;

void InitNode() {
	head = (student*)malloc(sizeof(student));
	if (head == NULL)
		return;
	head->next = NULL;
	member = head->next;
	tail = head;
}
void Import_studentData() {
	FILE* stfp = fopen("student.txt", "r");
	int ret = 0;
	while (1) {
		student* tmp = (student*)malloc(sizeof(student));
		if (tmp == NULL)
			return;
		ret = fscanf(stfp, "%s %s %s %c", tmp->stnum, tmp->passward, tmp->name, &tmp->lend);
		if (ret == EOF) break;
	tmp->next = head->next;
	head->next = tmp;
	}
	fclose(stfp);
}

int main() {
	int menu=0, m;
	FILE* stfp = fopen("student.txt", "w");
	fclose(stfp);

	InitNode();
	Import_studentData();
	while (1) {
		printf("\n[����������]\n\
1.ȸ������\n\
2.�α���\n\
3.����\n\
-----------------\n");
		m = scanf("%d", &menu);
		if (menu == 1)
			signUp();
		else if (menu == 2)
			logIn();
		else if (menu == 3)
			break;
	}
	Freedata();
	return 0;
}

void signUp() {
	int m;
	student* newstudent = (student*)malloc(sizeof(student));
	if (newstudent == 0)
		return;
	printf("�й� : ");
	m=scanf("%s", newstudent->stnum);
	printf("��й�ȣ : ");
	m=scanf("%s", newstudent->passward);
	printf("�̸� : ");
	m=scanf("%s", newstudent->name);
	newstudent->lend = 'N';
	newstudent->next = head->next;
	head->next = newstudent;
}

void logIn() {
	int m, loginError = 0, loginMenu;
	char studentNUM[20] = { 0 }, PW[20] = { 0 };
	while(1){
		student* tmp = head->next;
		printf("�й� : ");
		m = scanf("%s", studentNUM);
		while (member != NULL) {
			if (strcmp(studentNUM, member->stnum) != 0)
				member = member->next;
			else if (member->next == NULL)
				loginError = 1;
			else
				break;
		}
		printf("��й�ȣ : ");
		m = scanf("%s", PW);
		if (strcmp(PW, member->passward) == 0)
			;
		else
			loginError = 1;
	
		if (loginError == 1) {
			printf("\
	ERROR : �α��� ����\n\
	1. �ٽ� �α���\n\
	2. �������� ���ư���\n\
	3. ȸ������\n\
	---------------------------\n");
			m = scanf("%d", loginMenu);
			if (loginMenu == 1)
				;
			else if (loginMenu == 2)
				return;
			else if (loginMenu == 3)
				signUp();
		}
		else if (loginError == 0)
			;
	}
}
void Freedata() {

}