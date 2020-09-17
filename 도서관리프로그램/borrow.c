#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "borrow.h"
#include "student.h"
#include "book.h"

typedef struct borrow{
	char num[20];
	char isbn[10];
	struct borrow* next;

}borrow;

borrow* br_head;
borrow* br_tail;

void borrow_init(){ //대출연결리스트 초기화 함수
	br_head=(borrow*)malloc(sizeof(borrow));
	br_tail=br_head;
	br_head->next=NULL;	
}
                              
int confirm_stnum(char *st_num ){  // 존재하는 학번인지 확인하는 함수
	student *cf_node;
	cf_node=head;

	while(1){
		 if( cf_node  == NULL){
             printf("존재하지 않는 학번입니다.\n");
             return 3;
             }

		if(!strcmp(cf_node->stnum,st_num))
			break;

		cf_node=cf_node->next;
	}
	return 0;
}

int confirm_isbn(char *isbn){  //존재하는 isbn인지 확인하는 함수
	Book* cf_node;
	cf_node=Book_head;
	
	while(1){
		if(cf_node==NULL){
			printf("존재하지 않는 ISBN 입니다.\n");
			return 4;
		}

		if(!strcmp(cf_node->Book_ISBN,isbn ))
			break;
		cf_node=cf_node->next;
	}
	return 0;
}

void add_borrowlist(){ //도서대여 연결리스트
	borrow *new_node= (borrow*)malloc(sizeof(borrow));
	br_tail->next = new_node;
	br_tail= new_node;
	br_tail->next = NULL;

	int a;
	printf("[ 도서 대여 ]\n");
	printf("  학번: ");
	scanf("%s", new_node->num);
	a=confirm_stnum(new_node->num);
	if (a==3)
		return;

	int b;
	printf("  ISBN: ");
	scanf("%s", new_node->isbn);	
	b=confirm_isbn(new_node->isbn);
	if (b==4)
		return;
}

void save_borrow(){  //대출정보 저장
	FILE* brfp=fopen("borrow.txt","w");
	borrow *tmp=br_head->next;

	while(1){  //borrow연결리스트에 있는 정보탐색
		fprintf(brfp, "%s %s\n", tmp->num, tmp->isbn);
		if (tmp==NULL)
			break;
		tmp=tmp->next;
	}
	fclose(brfp);
}

void delete_borrow(){	//도서반납->대출연결리스트에서 삭제
	borrow* node=(borrow *)malloc(sizeof(borrow));
	borrow* delnode=br_head;
	borrow* backnode=delnode;
	int a,b;
	printf("학번 : ");
	scanf("%s",node->num);
	a=confirm_stnum(node->num);  //존재하는 학번인지 확인
	if (a==3)
		return;

	printf("ISBN : ");
	scanf("%s", node->isbn);
	b=confirm_isbn(node->isbn);   //존재하는 isbn인지 확인
	if (b==4)
		return;
	
	while(1){  //삭제할 노드 탐색
		if(delnode->next==NULL){
			printf("대출 정보를 찾을 수 없습니다.");
            return 1;
		}
		if(strcmp(node->num,delnode->num) == 0 && strcmp(node->isbn, delnode->isbn)==0){
			backnode=delnode->next;//노드삭제
			free(delnode);
			printf("반납되었습니다.");
			return 0;
		}
		backnode=delnode;
	    delnode=delnode->next;
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

	
	int main() {
	borrow_init();
	st_InitNode();
//	confirm_stnum;
//	confirm_isbn;
//	add_borrowlist();
//	save_borrow();
//	delete_borrow();
	Admin();
	}
