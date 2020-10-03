#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "borrow.h"
#include "book.h"

int withdraw();
void signUp();
void logIn();
void SuccessLogin_menu();
void student_free();
void MainMenu();
int FailLogin_menu();
int borrow_confirm();
void myBorrow_list();
void Update_studentData();
void st_InitNode();
void Import_studentData();

typedef struct student{
	struct student* next;

	char stnum[20];
	char passward[20];
	char name[20];
}student;


student* SThead;
student* member;

int main() {
//	FILE* fp = fopen("student.txt", "w");
//	fclose(fp);
	//기본 셋팅(대여)
	borrow_init();

	//기본 셋팅(도서)
	bk_init();
	Book_load();

	//기본 셋팅(학생)
	st_InitNode();
	Import_studentData();
	
	//시작메뉴
	MainMenu();
	return 0;
}

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
	//	printf("import");
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
	//	printf("Update");
	}
	fclose(fp);
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
	student_free();
	printf("===프로그램 종료===\n");
}

// 회원가입
void signUp() {
	int m;
	student* newstudent = (student*)malloc(sizeof(student));
	student* tmp = SThead;
	if (newstudent == NULL || tmp == NULL)
		return;
	printf("학번 : ");
	m=scanf("%s", newstudent->stnum); //myflush();

	printf("비밀번호 : ");
	m=scanf("%s", newstudent->passward);//myflush();
	printf("이름 : ");
	m=scanf("%s", newstudent->name);

	while(1){
		tmp=tmp->next;
		if(tmp == NULL) break;
		if(strcmp(newstudent->stnum, tmp->stnum) == 0){
			printf("이미 가입된 학번입니다.\n");
			free(newstudent);
			newstudent = NULL;
			return;
		}
	}

	newstudent->next = SThead->next;
	SThead->next = newstudent;
	Update_studentData();
/*	
	////////리스트 확인 코드/////////	
	tmp = SThead;
	while(tmp->next != NULL){
		tmp = tmp->next;
		printf("%s\n", tmp->stnum);
	}
	///////////////////////////////
*/
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
					member = NULL;
					Admin();
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
	printf("\n\
ERROR : 로그인 실패\n\
1. 다시 로그인\n\
2. 메인으로 돌아가기\n\
3. 회원가입\n\
---------------------------\n");
	scanf("%d", &FLMenu);
	return FLMenu;
}



void SuccessLogin_menu() {
	int SLmenu, BookReturn, wd;
	while(1){
		printf("\n\
[목록]\n\
1. 도서 검색\n\
2. 내 대여 목록\n\
3. 회원 탈퇴\n\
4. 로그아웃\n\
5. 프로그램 종료\n\
----------------------\n");
		int m = scanf("%d", &SLmenu);
		if (SLmenu == 1)
			Find_book();
		else if (SLmenu == 2)
			myBorrow_list();
		else if (SLmenu == 3){
			wd = withdraw();
			if(wd) //탈퇴 성공 -> 메인화면으로
				return;
			else if(!wd)
				printf("!error! 탈퇴 실패 : 반납하지 않은 도서가 있습니다. 도서를 반납한 후 회원 탈퇴가 가능합니다.\n");
		}
		else if (SLmenu == 4){
			member = NULL;
			return;
		}
		else if (SLmenu == 5){
			student_free();
			printf("====프로그램 종료====\n\n");
			exit(0);
		}
	}
}

//내 대여 목록 함수
void myBorrow_list(){
	int brnum=0;
	borrow *brtmp = br_head;
	Book *bktmp = Book_head;
	while(1){
		brtmp = brtmp->next;
		if(brtmp == NULL) break;
		//대출한 책이 있을 때
		if(!strcmp(brtmp->num,member->stnum)){
			//isbn 이용해서 책 이름 출력
			while(1){
				bktmp=bktmp->next;
				if(bktmp == NULL) break;
				if(!strcmp(bktmp->Book_ISBN, brtmp->isbn)){
					printf("%s\n", bktmp->Book_name);
					brnum++;
				}
			}
		}
	}
	if(brnum)
		printf("대출한 책의 수: %d\n", brnum);
	else
		printf("대출한 책이 없습니다.\n");
}

//회원 탈퇴 함수 ==> 대출목록 확인 후 회원 탈퇴
int withdraw(){
	int brconfirm;
	brconfirm = borrow_confirm();
	if(!brconfirm){
		student *tmp = SThead;
		while(tmp->next != member)
			tmp=tmp->next;
		tmp->next = member->next;
		free(member);
		member = NULL;
		Update_studentData();
		printf("--회원 탈퇴--\n");
		return 1;
	}
	else
		return 0;
}


//대출 확인
int borrow_confirm(){
	borrow *brtmp = br_head;
	while(brtmp != NULL){
		brtmp=brtmp->next;
		if(brtmp==NULL) break;
		if(strcmp(member->stnum,brtmp->num)==0) return 1;
	}
	return 0;
}


void student_free() {
	student *tmp = SThead;
	while (tmp != NULL){
		SThead = SThead->next;
		free(tmp);
		tmp = SThead;
	}
	tmp = NULL;
	SThead = NULL;
	member = NULL;
}
