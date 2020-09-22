#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"


void signUp();
void logIn();
void SuccessLogin_menu();
void StudentFreedata();

typedef struct student{
	struct student* next;
	char stnum[20];
	char passward[20];
	char name[20];
}student;

student* SThead;
student* member;

void st_InitNode() {
	SThead = (student*)malloc(sizeof(student));
	if (SThead == NULL)
		return;
	SThead->next = NULL;
	member = SThead->next;
}

//�л� ���� (����Ʈ��) ��������
void Import_studentData() {
	FILE* stfp = fopen("student.txt", "r");
	int ret = 0;
	while (1) {
		student* tmp = (student*)malloc(sizeof(student));
		if (tmp == NULL)
			return;
		ret = fscanf(stfp, "%s %s %s", tmp->stnum, tmp->passward, tmp->name);
		if (ret == EOF) break;
	tmp->next = SThead->next;
	SThead->next = tmp;
	}
	fclose(stfp);
}

void Update_studentData() {   //����Ʈ���� ���Ϸ� �Է����ִ� �Լ� 
	FILE* fp = fopen("bk.txt", "w");
	student* tmp = (student*)malloc(sizeof(student));
	tmp = SThead->next;
	while (tmp != NULL) {
		fprintf(fp, "%s %s %s", tmp->stnum, tmp->passward, tmp->name);
		tmp = tmp->next;
	}
	fclose(fp);
}

int main() {
	int menu=0, m;
	FILE* stfp = fopen("student.txt", "w");
	fclose(stfp);

	bk_init();
	st_InitNode();
	Import_studentData();
	Book_load();
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
		else if (menu == 3) {
			printf("===���α׷� ����===");
			break;
		}
	}
	StudentFreedata();
	return 0;
}

// ȸ������
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
	newstudent->next = SThead->next;
	SThead->next = newstudent;
	Update_studentData();
}

// �α���
void logIn() {
	int m, loginError = 1, loginMenu;
	char studentNUM[20] = { 0 }, PW[20] = { 0 }, i=1;
	while (i){
		member = SThead->next;
		printf("�й� : ");
		m = scanf("%s", studentNUM);
		printf("��й�ȣ : ");
		m = scanf("%s", PW);

		do {
			member = member->next;
			if (member == NULL) 
				break;

			if (strcmp(studentNUM, member->stnum) == 0 && strcmp(PW, member->passward) == 0) {
				//�й� & ��� ��ġ
					i = 0;	loginError = 0;
					SuccessLogin_menu();
					break;
			}

			else if (strcmp(studentNUM, "admin") == 0 && strcmp(PW, "admin") == 0) {
			//������ ���
					i = 0;	loginError = 0;
					Admin();
					break;
			}

			else{
			//�й� or ��� ��ġX
				if (member->next != NULL)
				continue;
			}
		} while (member != NULL);

// �α��� ���н�
		if (loginError == 1) {
			printf("\
ERROR : �α��� ����\n\
1. �ٽ� �α���\n\
2. �������� ���ư���\n\
3. ȸ������\n\
---------------------------\n");
			m = scanf("%d", &loginMenu);
			if (loginMenu == 1)
				continue;
			else if (loginMenu == 2)
				return;
			else if (loginMenu == 3) {
				signUp();
				break;
			}
		}
		else if (loginError == 0)
			break;
	}
}

void SuccessLogin_menu() {
	int SLmenu, BookReturn;
	printf("\n\
[���]\n\
1. ���� �˻�\n\
2. �� �뿩 ���\n\
3. ȸ�� Ż��\n\
4. �α׾ƿ�\n\
5. ���α׷� ����\n");
	int m = scanf("%d", &SLmenu);
	if (SLmenu == 1)
		BookReturn = Find_book();
	else if (SLmenu == 2)
		//�� �뿩 ��� ã�� �Լ� �߰�
		;
	else if (SLmenu == 3)
		//ȸ�� Ż�� �Լ� �߰�(���� ��Ͽ� �̸� ������ �Ұ�, ���� �� txt���� ������Ʈ)
		Update_studentData();
	else if (SLmenu == 4)
		return;
	else if (SLmenu == 5){
		StudentFreedata();
		exit(-1);
	}
}

void StudentFreedata() {
	Update_studentData();
	student* tmp;
	while (SThead->next != NULL) {
		tmp = SThead;
		if (tmp->next == NULL)
			free(tmp);
		else
			tmp = tmp->next;
	}
	free(SThead);
}