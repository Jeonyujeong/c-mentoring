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
	printf("%d번째 학생 이름 : ", num);
	m=scanf("%s", newstudent->name);
	printf("국어 점수 : ");
	scanf_s("%d", &newstudent->kor);
	printf("영어 점수 : ");
	scanf_s("%d", &newstudent->eng);
	printf("수학 점수 : ");
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
 이름  국어 영어 수학 총점 평균\n\
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
1.성적입력\n\
2.성적확인\n\
3.종료\n\
-------------\n\
선택 ( 1 ~ 3 ) : ");
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
			printf("프로그램이 종료됩니다.\n");
			break;
		}
	}
	return 0;
}