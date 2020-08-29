#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct Book{
	char Book_name[30];
	char Book_company[30];
	char Book_ISBN[20];
	char Book_author[20];
	char Book_borrow; 
	struct Book *next;
	
}Book;

Book *Book_head;
Book *Book_tmp;
Book *ttmp;
Book *ttmp_back;
void init(){
	Book_head=(Book *)malloc(sizeof(Book));
	Book_head->next=NULL;
	Book_tmp=Book_head;	
}


void Admin_mode(){
	printf("[관리자 모드]\n");
	printf("1. 도서 등록\n");
	printf("2. 도서 삭제\n");
	printf("3. 도서 대여\n");
	printf("4. 도서 반납\n");
	printf("5. 도서 검색\n");
	printf("6. 회원 목록\n");
	printf("7. 로그아웃\n");
	printf("8.프로그램 종료\n");
}

void add_book(){
	Book *p=(Book *)malloc(sizeof(Book));
	
	printf("[ 도서 등록 ]\n");
	printf("도서명:");
	scanf("%s",p->Book_name);
	printf("출판사:");
	scanf("%s",p->Book_company);
	printf("저자명:");
	scanf("%s",p->Book_author);
	printf("ISBN:");
	scanf("%s",p->Book_ISBN);
	printf("대출가능 여부:");
	scanf("%c",p->Book_borrow);
	p->next=NULL;
	
	Book_tmp->next=p;
	Book_tmp=Book_tmp->next;
	
	
}

void remove_book(){
	char name[30];
	printf("도서명:");
	scanf("%s",name);
	ttmp=head->next;
	ttmp_back=head;
	while(1){
		if(strcmp(ttmp->Book_name,name)==0){
			ttmp_back->next=
	}
		
	}
}
void Book_load(){
	char name[30];
	char company[30];
	char ISBN[20];
	char author[20];
	char borrow;
	
	
	FILE* fp=fopen("book.txt","r");
	int ret=0;
	printf("%d", ret);
	while(1){
		printf("1");
		Book *q=(Book *)malloc(sizeof(Book));
		q->next=NULL;
		
		ret=fscanf(fp,"%s %s %s %s %c",name,company,author,ISBN,&borrow);
		printf("%d", ret);
		printf("%s %s %s %s %c",name,company,author,ISBN,borrow);
		
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

void books(){
	ttmp=Book_head->next;
	while(ttmp!=NULL){
		printf("%s %s %s %s %c\n",ttmp->Book_name,ttmp->Book_company,ttmp->Book_author,ttmp->Book_ISBN,ttmp->Book_borrow);
		ttmp=ttmp->next;
			
	}

}


int main(){
	
	init();
	add_book();
	

	return 0;
}
