#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "book.h"
#include "student.h"
#include "borrow.h"


#define Book_name_size 100
#define Book_company_size 30
#define Book_ISBN_size 20
#define Book_author_size 20




/*
typedef struct Book{      //도서 목록 링크드리스트
	char Book_name[Book_name_size];
	char Book_company[Book_company_size];
	char Book_ISBN[Book_ISBN_size];
	char Book_author[Book_author_size];
	char Book_borrow;
	struct Book *next;

}Book;
Book *Book_head;
Book *Book_tmp; //맨 끝 책 위치
Book *ttmp;
Book *ttmp_back;
*/

void bk_init(){                          // book 리스트 맨 처음부분 만드는 함수

	Book_head=(Book *)malloc(sizeof(Book));

	Book_head->next=NULL;
	Book_tmp=Book_head;
}



int Admin_mode(){                      //관리자 모드 출력 함수 ,선택 수 리턴
	int choice;
	printf("\n[관리자 모드]\n");
	printf("1. 도서 등록\n");
	printf("2. 도서 삭제\n");
	printf("3. 도서 대여\n");
	printf("4. 도서 반납\n");
	printf("5. 도서 검색\n");
	printf("6. 회원 목록\n");
	printf("7. 로그아웃\n");
	printf("8.프로그램 종료\n");

	scanf("%d",&choice);
	return choice;
}



void add_book(){                 //도서 등록 함수
	Book *p=(Book *)malloc(sizeof(Book));

	printf("[ 도서 등록 ]\n");
	printf("도서명:");
	getchar();
	fgets(p->Book_name,Book_name_size,stdin);
	Erase_enter(p->Book_name);
	printf("출판사:");
	fgets(p->Book_company,Book_name_size,stdin);
	Erase_enter(p->Book_company);
	printf("저자명:");
	fgets(p->Book_author,Book_name_size,stdin);
	Erase_enter(p->Book_author);
	printf("ISBN:");
	fgets(p->Book_ISBN,Book_name_size,stdin);
	Erase_enter(p->Book_ISBN);

	printf("대출가능 여부(y/n):");
	scanf("%c",&p->Book_borrow);
	getchar();
	while(p->Book_borrow!='y'&&p->Book_borrow!='n'){
		printf("'y'와 'n'중 하나를 입력해 주십시오 :");
		scanf("%c",&p->Book_borrow);
		getchar();

	}
	p->next=NULL;

	Book_tmp->next=p;
	Book_tmp=Book_tmp->next;

	/*FILE* fp=fopen("bk.txt","w");
	fprintf(fp,"%s %s %s %s %c\n",p->Book_name,p->Book_company,p->Book_author,p->Book_ISBN,p->Book_borrow);
	fclose(fp);
	*/
}

void remove_book(){              // 도서 삭제 함수
	char name[Book_name_size];
	printf("도서명:");
	scanf("%s",name);
	ttmp=Book_head->next;
	ttmp_back=Book_head;
	while(ttmp!=NULL&&strcmp(ttmp->Book_name,name)!=0){
		ttmp_back=ttmp;
		ttmp=ttmp->next;
	}
	if(ttmp==NULL){
		printf("%s란 도서를 찾을 수 없습니다.\n",name);
	}else{
		if(ttmp->Book_borrow=='n'){
			printf("대출중인 책은 삭제가 불가능합니다.\n");
		}else{

			ttmp_back->next=ttmp->next;
			free(ttmp);
			printf("삭제가 완료되었습니다.\n");
			Load_list_to_file();
		}


	}
}

void borrow_book(){        //도서 대여 함수
char student[10];
char ISBN[Book_ISBN_size];
	printf("[도서대여]\n");
	printf("학번 :");

	scanf("%s",student);
	printf("ISBN :");
	 scanf("%s",ISBN);
	 //학생 리스트 이용해서...(학번에 맞는 학생 있으면 대출해줌(학생 목록에 책도 추가해준다)
	 ttmp=Book_head->next;
	 while(ttmp!=NULL&&strcmp(ttmp->Book_ISBN,ISBN)!=0){
		 ttmp=ttmp->next;
	 }
	 if(ttmp==NULL){
	 	printf("존재하지 않는 도서입니다.\n") ;
	 }else{

	 	if(strcmp(ttmp->Book_ISBN,ISBN)==0){
	 		if(ttmp->Book_borrow=='n'){
	 			printf("이미 대출된 도서입니다.\n");

			 }else{
			 	printf("'%s'책이 대출되었습니다.\n",ttmp->Book_name);
			 	ttmp->Book_borrow='n';
			 	Load_list_to_file();

			 }

		 }
	 }

}

Book* ISBN_cmp(char ISBN[Book_ISBN_size]){  //isbn을 받아 링스드리스트 안에서 비교해서 book노드 주소 반환하는 함수

	ttmp=Book_head->next;

	while(ttmp!=NULL&&strcmp(ttmp->Book_ISBN,ISBN)!=0){
		 ttmp=ttmp->next;
	}
	return ttmp;
}

void return_book(){      //도서 반납 함수

	char ISBN[Book_ISBN_size];
	printf("ISBN:");
	scanf("%s",ISBN);

	q=ISBN_cmp(ISBN);

	if(q==NULL){
	 	printf("존재하지 않는 도서입니다.\n") ;
	}else{

	 	if(strcmp(q->Book_ISBN,ISBN)==0){
	 		if(ttmp->Book_borrow=='y'){
	 			printf("이미 반납된 도서입니다.\n");

			 }else{
			 	printf("'%s'책이 반납되었습니다.\n",q->Book_name);
			 	q->Book_borrow='y';
			 	Load_list_to_file();

			 }

		 }
	 }

}

void Load_list_to_file(){   //리스트에서 파일로 입력해주는 함수
	FILE* fp= fopen("bk.txt","w");
	ttmp=Book_head->next;
	while(ttmp!=NULL){
		fprintf(fp,"%s %s %s %s %c\n",ttmp->Book_name,ttmp->Book_company,ttmp->Book_author,ttmp->Book_ISBN,ttmp->Book_borrow);
		ttmp=ttmp->next;
	}
	fclose(fp);
}


void Book_load(){                  //파일에서 링크드리스트로 만드는 함수->실행 안해봄
	char name[Book_name_size];
	char company[Book_company_size];
	char ISBN[Book_ISBN_size];
	char author[Book_author_size];
	char borrow;


	FILE* fp=fopen("bk.txt","r");
	int ret=0;

	while(1){

		Book *q=(Book *)malloc(sizeof(Book));
		q->next=NULL;

		ret=fscanf(fp,"%s %s %s %s %c",name,company,author,ISBN,&borrow);
		if (ret==EOF)
			break;
		//printf("%s %s %s %s %c",name,company,author,ISBN,borrow);

		strcpy(q->Book_name,name);
		strcpy(q->Book_company,company);
		strcpy(q->Book_ISBN,ISBN);
		strcpy(q->Book_author,author);

		q->Book_borrow=borrow;

		Book_tmp->next=q;
		Book_tmp=q;

		if(ret==EOF)
		break;

	}
	fclose(fp);
}


int Find_book(){        //[도서검색]창  ,번호 리턴

	int num;
	while(1){

	printf("\n[도서검색]\n");
	printf("1. 도서명 검색\n");
	printf("2. 출판사 검색\n");
	printf("3. ISBN 검색\n");
	printf("4. 저자명 검색\n");
	printf("5. 전체 검색\n");
	printf("6. 이전 메뉴\n");
	scanf("%d",&num);

	if(num==1){
		Search_book_name();
	}else if(num==2){
		Search_book_company();
	}else if(num==3){
		char isbn[Book_ISBN_size];

		printf("ISBN: ");
		scanf("%s",isbn);
		q=ISBN_cmp(isbn);

		if(q==NULL){
			printf("존재하지 않는 도서입니다.\n");
		}else{
			Book_information(q);
		}
	}else if(num==4){
		Search_book_author();

	}else if(num==5){
		books();
	}else if(num==6){
		break;
	}else{
		printf("1~6사이의 수를 입력해 주십시오\n");
	}
	}
}

void Search_book_author(){   //저자명 찾아주는 함수

	char author[Book_author_size];
	printf("저자명 :");
	getchar();
	fgets(author,Book_author_size,stdin);
	Erase_enter(author);

	ttmp=Book_head->next;
	int nu=0;

	while(ttmp!=NULL){
		if(Find_word(author,ttmp->Book_author)==1){
			Book_information(ttmp);
			nu++;
		}
		ttmp_back=ttmp;
		ttmp=ttmp->next;
	}

	if(nu==0){
		printf("저자명이 %s인 도서를 찾을 수 없습니다.\n",author);
	}else{
		printf("\n총 %d권의 책이 검색되었습니다.\n",nu);
	}
}

void Search_book_company(){        //출판사 찾는 함수

	char company[Book_company_size];
	printf("출판사명 :");
	getchar();
	fgets(company,Book_company_size,stdin);
	Erase_enter(company);

	ttmp=Book_head->next;
	int nu=0;

	while(ttmp!=NULL){
		if(Find_word(company,ttmp->Book_company)==1){
			Book_information(ttmp);
			nu++;
		}
		ttmp_back=ttmp;
		ttmp=ttmp->next;
	}

	if(nu==0){
		printf("출판사가  %s인 도서를 찾을 수 없습니다.\n",company);
	}else{
		printf("\n총 %d권의 책이 검색되었습니다.\n",nu);
	}
}

void Book_information(Book *node){      //노드 주소를 받아 정보를 다 출력해주는 함수

	printf("\n도서명 : %s\n",node->Book_name);
	printf("출판사 : %s\n",node->Book_company);
	printf("ISBN : %s\n",node->Book_ISBN);
	printf("저자명 : %s\n",node->Book_author);
	printf("대출여부 : %c\n",node->Book_borrow);

}


void Erase_enter(char *s){  //개행문자 지워주는 함수
	s[strlen(s)-1]='\0';
}

void Search_book_name(){         //도서명 검색 함수
	char name[Book_name_size];
	printf("책이름: ");
	getchar();
	fgets(name,Book_name_size,stdin);
	Erase_enter(name);

	ttmp=Book_head->next;
	int nu=0;
	while(ttmp!=NULL){
		if(Find_word(name,ttmp->Book_name)==1){
			Book_information(ttmp);
			nu++;
		}
		ttmp_back=ttmp;
		ttmp=ttmp->next;
	}
	if(nu==0){
		printf("%s란 도서를 찾을 수 없습니다.\n",name);
	}else{
		printf("총 %d권의 책이 검색되었습니다.\n",nu);
	}

}

int Find_word(char *a,char *b){       //단어 찾기 함수

	if(strstr(b,a)==NULL){
		return 0;
	}else{
		return 1;
	}

}

void books(){
	ttmp=Book_head->next;
	while(ttmp!=NULL){
		printf("%s %s %s %s %c\n",ttmp->Book_name,ttmp->Book_company,ttmp->Book_author,ttmp->Book_ISBN,ttmp->Book_borrow);
		ttmp=ttmp->next;

	}

}
void Admin(){     //관리자모드

		while(1){

	int c_num=0;
	c_num=Admin_mode();           ///문자 입력시 무한수열 이유...?

	if(c_num==1){
		add_book();
		Load_list_to_file();
	}else if(c_num==2){
		remove_book();

	}else if(c_num==3){
		add_borrowlist();
		save_borrow();
	}else if(c_num==4){
		delete_borrow();
	}else if(c_num==5){
		Find_book();

	}else if(c_num==6){
		//효원이 학생 연결리스트 불러오기

	}else if(c_num==7){
	 //맨 처음 [도서관 서비스]로 이동
	}else if(c_num==8){
		break;
	}else{
	  printf("1부터 8까지의 수 중 하나를 입력해 주십시오.\n");
	  fflush(stdin);
	}



}
}

/*
int main(){

	bk_init();
	Login();
	return 0;
}
*/
