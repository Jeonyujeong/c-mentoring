#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "book.h"


void signUp();
void logIn();
void SuccessLogin_menu();
void StudentFreedata();
void MainMenu();
int FailLogin_menu();

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
	member = SThead;
}

//학생 정보 (리스트로) 가져오기
void Import_studentData() {
	FILE* stfp = fopen("student.txt", "r");
	int ret = 0;
	while (1) {
		student* tmp = (student*)malloc(sizeof(student));
		if (tmp == NULL)
			return;
		ret = fscanf(stfp, "%s %s %s\n", tmp->stnum, tmp->passward, tmp->name);
		if (ret == EOF) break;
		printf("import");
		tmp->next = SThead->next;
		SThead->next = tmp;	
		tmp = NULL;
	}
	fclose(stfp);
}

void Update_studentData() {   //리스트에서 파일로 입력해주는 함수 
	FILE* fp = fopen("student.txt", "w");
	student* tmp = SThead;
	while (1) {
		tmp= tmp->next;
		if(tmp == NULL) break;
		fprintf(fp, "%s %s %s\n", tmp->stnum, tmp->passward, tmp->name);
		printf("Update");
	}
	fclose(fp);
}

int main() {
	//student.txt 파일 생성(오류 방지)
	FILE* stfp = fopen("student.txt", "w");
	fclose(stfp);

//	Book_load();
//	bk_init();

	//기본 셋팅(학생)
	st_InitNode();
	Import_studentData();
	
	//시작메뉴
	MainMenu();
	return 0;
}

void MainMenu(){
	int menu=0;
	while (1) {
		printf("\n\
[도서관서비스]\n\
1.회원가입\n\
2.로그인\n\
3.종료\n\
-----------------\n");
		scanf("%d", &menu);
		if (menu == 1)
			signUp();
		else if (menu == 2)
			logIn();
		else if (menu == 3) {
			break;
		}
	}
	StudentFreedata();
	printf("===프로그램 종료===");
}

// 회원가입
void signUp() {
	int m;
	student* newstudent = (student*)malloc(sizeof(student));
	student* tmp = SThead;
	if (newstudent == NULL || tmp == NULL)
		return;
	printf("학번 : ");
	m=scanf("%s", newstudent->stnum);
	printf("비밀번호 : ");
	m=scanf("%s", newstudent->passward);
	printf("이름 : ");
	m=scanf("%s", newstudent->name);
	while(tmp->next != NULL){
		tmp=tmp->next;
		if(newstudent->stnum == tmp->stnum){
			printf("이미 가입된 학번입니다.");
			return;
		}
	}
	newstudent->next = SThead->next;
	SThead->next = newstudent;
	Update_studentData();
	
	////////리스트 확인 코드/////////	
	tmp = SThead;
	while(tmp->next != NULL){
		tmp = tmp->next;
		printf("%s\n", tmp->stnum);
	}
	///////////////////////////////

	tmp = NULL;
	newstudent = NULL;
}	

// 로그인
void logIn() {
	int FLMenu, loginError = 1;
	char studentNUM[20] = { 0 }, PW[20] = { 0 };
	_Bool i=1;
	while (i){
		//member = SThead->next; ==> member = SThead;
		member = SThead;
		printf("학번 : ");
		scanf("%s", studentNUM);
		printf("비밀번호 : ");
		scanf("%s", PW);

		do {
			member = member->next;
			if (member == NULL) 
				break;

			if ((strcmp(studentNUM, member->stnum)) == 0 && (strcmp(PW, member->passward) == 0)) {
				//학번 & 비번 일치
					i = 0;	loginError = 0;
					SuccessLogin_menu();
					break;
			}

			else if ((strcmp(studentNUM, "admin")) == 0 && (strcmp(PW, "admin") == 0)) {
			//관리자 모드
					i = 0;	loginError = 0;
//					Admin();
					break;
			}

		else{
		//학번 or 비번 일치X
			//+비교할 학생 데이터 남아있을 때
			if (member->next != NULL)
				continue;
			else
				break;
		}
		} while (member != NULL);

// 로그인 실패시
		if (loginError == 1){
			FLMenu = FailLogin_menu();
			if (FLMenu == 1)
				continue;
			else if (FLMenu == 2)
				return;
			else if (FLMenu == 3) {
				signUp();
				break;
			}
		}

		else if (loginError == 0)
			return;
	}
}	



int FailLogin_menu(){
	int FLMenu;
	printf("\
ERROR : 로그인 실패\n\
1. 다시 로그인\n\
2. 메인으로 돌아가기\n\
3. 회원가입\n\
---------------------------\n");
	scanf("%d", &FLMenu);
	return FLMenu;
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
	int m = scanf("%d", &SLmenu);
	if (SLmenu == 1)
//		BookReturn = Find_book();
		;
	else if (SLmenu == 2)
		//내 대여 목록 찾는 함수 추가
		;
	else if (SLmenu == 3)
		//회원 탈퇴 함수 추가(대출 목록에 이름 있으면 불가, 삭제 후 txt파일 업데이트)
		Update_studentData();
	else if (SLmenu == 4){
		member = NULL;
		return;
	}
	else if (SLmenu == 5){
		StudentFreedata();
		exit(0);
	}
}

void StudentFreedata() {
//	Update_studentData();
	printf("데이터 free 함수");
	while (SThead != NULL){
		student* tmp = SThead;
		while(tmp->next != NULL){
			free(tmp);
			printf("free");
			continue;
		}
		tmp = tmp->next;
		tmp = NULL;
	}
	SThead = NULL;
	member = NULL;
}
