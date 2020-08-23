#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	struct student* next;
	char name[10];
	int kor;
	int eng;
	int math;
	int sum;
	int ave;
}student;

student* head;

void initStudent() {
	head = (student*)malloc(sizeof(student));
	if (head == NULL)
		return;
	head->next = NULL;
}

void InputData(int num) {
	int m, i = 0;
	student* newstudent = (student*)malloc(sizeof(student));
	if (newstudent == NULL)
		return;
	//새로운 데이터 입력
	printf("%d번째 학생 이름 : ", num);
	m = scanf("%s", newstudent->name);
	printf("국어 점수 : ");
	scanf_s("%d", &newstudent->kor);
	printf("영어 점수 : ");
	scanf_s("%d", &newstudent->eng);
	printf("수학 점수 : ");
	scanf_s("%d", &newstudent->math);
	newstudent->sum = newstudent->kor + newstudent->eng + newstudent->math;
	newstudent->ave = newstudent->sum / 3;

	newstudent->next = NULL;
	student* tmp = head;
	while (tmp->next != NULL) {
		//새로운 학생의 점수가 클 때
		if (((newstudent->sum) > (tmp->next->sum)) && i == 0) {
			newstudent->next = tmp->next;
			tmp->next = newstudent;
			i++;
		}
		//기존 학생의 점수가 클 때
		else
			tmp = tmp->next;
	}
	if ((tmp->next == NULL) && (i == 0))
		tmp->next = newstudent;
}


void DataOutput() {
	int num = 0;
	student* curr = head->next;
	if (head->next != NULL) {
		printf("\n\
   ------------------------------------\n\
    이름  국어 영어 수학 총점 평균 등수\n\
   ------------------------------------\n");
		while (curr != NULL) {
			printf("%8s%4d %4d %4d %4d %4d %3d등\n", curr->name, curr->kor, curr->eng, curr->math, curr->sum, curr->ave, ++num);
			curr = curr->next;
		}
	}
	else
		return;
}

void FreeData() {
	student* tmp;
	while (head->next != NULL)
	{	
		tmp = head;
		if (tmp->next == NULL)
			free(tmp);
		else
			tmp = tmp->next;
	}
	free(head);
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
	int cho, i = 1;
	initStudent();
	while (1) {
		cho = menu();
		if (cho == 1) {
			InputData(i);
			i++;
		}
		else if (cho == 2)
			DataOutput();
		else if (cho == 3) {
			printf("프로그램이 종료됩니다.\n");
			FreeData();
			break;
		}
	}
	return 0;
}