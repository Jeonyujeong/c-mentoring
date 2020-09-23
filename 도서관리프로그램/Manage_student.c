#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "student.h"
#include "book.h"


void signUp();
void logIn();
void SuccessLogin_menu();
void StudentFreedata();

typedef struct stNode{
	struct stNode* next;
	char stnum[20];
	char passward[20];
	char name[20];
}student;

student* stHead;
student* member;

void myflush() {
	while(getchar() != '\n');
}

void st_InitNode() {
	stHead = (student*)malloc(sizeof(student));
	if (stHead == NULL)
		return;
	stHead->next = NULL;
	member = stHead->next;
}

//학생 정보 (리스트로) 가져오기
void Import_studentData() {
	FILE* stfp = fopen("student.txt", "r");
	int ret = 0;
	while (1) {
		student* tmp = (student*)malloc(sizeof(student));
		if (tmp == NULL)
			return;
		ret = fscanf(stfp, "%s %s %s", tmp->stnum, tmp->passward, tmp->name);
		if (ret == EOF) break;
	tmp->next = stHead->next;
	stHead->next = tmp;
	}
	fclose(stfp);
}

void Update_studentData() {   //리스트에서 파일로 입력해주는 함수
	FILE* fp = fopen("bk.txt", "w");
	student* tmp = (student*)malloc(sizeof(student));
	tmp = stHead->next;
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
		printf("\n[도서관서비스]\n\
1.회원가입\n\
2.로그인\n\
3.종료\n\
-----------------\n");

		m = scanf("%d", &menu);
		if (menu == 1)
			signUp();
		else if (menu == 2)
			logIn();
		else if (menu == 3) {
			printf("===프로그램 종료===");
			break;
		}
	}
	StudentFreedata();
	return 0;
}

// 회원가입
void signUp() {
	int m;
	student* newstudent = (student*)malloc(sizeof(student));
	if (newstudent == 0)
		return;
	printf("학번 : ");
	m=scanf("%s", newstudent->stnum); myflush();
	printf("비밀번호 : ");
	m=scanf("%s", newstudent->passward);myflush();
	printf("이름 : ");
	m=scanf("%s", newstudent->name);myflush();
	newstudent->next = stHead->next;
	stHead->next = newstudent;
	Update_studentData();
}

// 로그인
void logIn() {
	int m, loginError = 1, loginMenu;
	char studentNUM[20] = { 0 }, PW[20] = { 0 }, i=1;
	while (i){
		member = stHead->next;
		printf("학번 : ");
		m = scanf("%s", studentNUM);myflush();
		printf("비밀번호 : ");
		m = scanf("%s", PW);myflush();

		printf("%s, %s\n", studentNUM, PW);
		/*
		학번 = studentNUM, 비밀번호 = PW 로 입력 받음.
		member에 저장하는 부분없음 -> 계속 로그인 실패

		do while 문을 사용하긴 했지만 그냥 while문 사용해되 될듯해
		if - break 문이 있기 때문에 while 문에 조건을 안써도 됨.
		*/

		do {
			member = member->next;
			if (member == NULL)
				break;

			if (strcmp(studentNUM, member->stnum) == 0 && strcmp(PW, member->passward) == 0) {
				//학번 & 비번 일치
					i = 0;	loginError = 0;
					SuccessLogin_menu();
					break;
			}

			else if (strcmp(studentNUM, "admin") == 0 && strcmp(PW, "admin") == 0) {
			//관리자 모드
					i = 0;	loginError = 0;
					Admin();
					break;
			}

			else{
			//학번 or 비번 일치X
				if (member->next != NULL)
				continue;
			}
		} while (member != NULL);

// 로그인 실패시
		if (loginError == 1) {
			printf("\
ERROR : 로그인 실패\n\
1. 다시 로그인\n\
2. 메인으로 돌아가기\n\
3. 회원가입\n\
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
[목록]\n\
1. 도서 검색\n\
2. 내 대여 목록\n\
3. 회원 탈퇴\n\
4. 로그아웃\n\
5. 프로그램 종료\n");
	scanf("%d", &SLmenu);
	if (SLmenu == 1)
		BookReturn = Find_book();
	else if (SLmenu == 2)
		//내 대여 목록 찾는 함수 추가
		;
	else if (SLmenu == 3)
		//회원 탈퇴 함수 추가(대출 목록에 이름 있으면 불가, 삭제 후 txt파일 업데이트)
		Update_studentData();
	else if (SLmenu == 4)
		return;
	else if (SLmenu == 5){
		StudentFreedata();
		exit(1);
	}
}

void StudentFreedata() {
	Update_studentData();
	student* tmp;
	while (stHead->next != NULL) {
		tmp = stHead;
		if (tmp->next == NULL)
			free(tmp);
		else
			tmp = tmp->next;
	}
	free(stHead);
}
