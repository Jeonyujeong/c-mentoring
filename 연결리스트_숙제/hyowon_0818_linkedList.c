#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	struct student* next;
	char name[10];
	int kor;
	int eng;
	int math;
}student;

student* head;
student* tail;

void initStudent() {
	head = (student*)malloc(sizeof(student));
	if (head == NULL)
		return;
	tail = head;
	head->next = NULL;
}

void insert_score(int num) {
	int m;
	student* newstudent = (student*)malloc(sizeof(student));
	if (newstudent == NULL)
		return;
	printf("%d��° �л� �̸� : ", num);
	m=scanf("%s", newstudent->name);
	printf("���� ���� : ");
	scanf_s("%d", &newstudent->kor);
	printf("���� ���� : ");
	scanf_s("%d", &newstudent->eng);
	printf("���� ���� : ");
	scanf_s("%d", &newstudent->math);
	newstudent->next = NULL;
	tail->next = newstudent;
	tail = newstudent;
}
void data_output() {
	int sum;
	student* curr = head->next;
	printf("\n\
--------------------------------\n\
 �̸�  ���� ���� ���� ���� ���\n\
--------------------------------\n");
	while (curr != NULL) {
		sum = curr->kor + curr->eng + curr->math;
		printf("%5s%4d %4d %4d %4d %4d\n", curr->name, curr->kor, curr->eng, curr->math, sum, (sum/3));
		curr = curr->next;
	}
}
int menu() {
	int choice;
	printf("\n\
[Menu]\n\
1.�����Է�\n\
2.����Ȯ��\n\
3.����\n\
-------------\n\
���� ( 1 ~ 3 ) : ");
	scanf_s("%d", &choice);
	return choice;
}
int main() {
	int cho, i=1;
	initStudent();
	while (1) {
		cho = menu();
		if (cho == 1){
			insert_score(i);
			i++;
		}
		else if (cho == 2)
			data_output();
		else if (cho == 3) {
			printf("���α׷��� ����˴ϴ�.\n");
			break;
		}
	}
	return 0;
}