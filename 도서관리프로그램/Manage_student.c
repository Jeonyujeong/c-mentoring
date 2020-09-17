#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

/*
typedef struct stNode{
	struct stNode* next;
	char stnum[20];
	char passward[20];
	char name[20];
}student;

student* head;
student* tail;
student* member;
*/

void st_InitNode() {
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
		ret = fscanf(stfp, "%s %s %s", tmp->stnum, tmp->passward, tmp->name);
		if (ret == EOF) break;
	tmp->next = head->next;
	head->next = tmp;
	}
	fclose(stfp);
}
/*
int main() {
	int menu=0, m;
	FILE* stfp = fopen("student.txt", "w");
	fclose(stfp);

	st_InitNode();
	Import_studentData();
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
		else if (menu == 3)
			break;
	}
	Freedata();
	return 0;
}
*/
void signUp() {
	int m;
	student* newstudent = (student*)malloc(sizeof(student));
	if (newstudent == 0)
		return;
	printf("학번 : ");
	m=scanf("%s", newstudent->stnum);
	printf("비밀번호 : ");
	m=scanf("%s", newstudent->passward);
	printf("이름 : ");
	m=scanf("%s", newstudent->name);
	newstudent->next = head->next;
	head->next = newstudent;
}

void logIn() {
	int m, loginError = 0, loginMenu;
	char studentNUM[20] = { 0 }, PW[20] = { 0 }, i=1;
	while (i){
/// 로그인 ///
		member = head->next;
			printf("학번 : ");
			m = scanf("%s", studentNUM);
			printf("비밀번호 : ");
			m = scanf("%s", PW);

		do {
				if (member == NULL) {
					loginError = 1;
					break;
				}
			if (strcmp(studentNUM, member->stnum) == 0) {
				if (strcmp(PW, member->passward) == 0) {
					loginError = 0;
					i = 0;
					break;
				}
				else {
					loginError = 1;
					if (member->next != NULL)
						continue;
				}
			}
			else{
				loginError = 1;
				if (member->next != NULL)
					continue;
			}
			member = member->next;
		} while (member != NULL);

/// 로그인 실패시 ///
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
		//로그인 성공->도서 관리로 넘어가기
		else if (loginError == 0)
			break;
	}
}
void Freedata() {

}
