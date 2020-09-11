#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "borrow.h"
#include "student.h"
#include "book.h"
/*
typedef struct borrow{
	int num;
	char isbn[10];
	struct borrow* next;

}borrow;

borrow* br_head;
borrow* br_tail;
*/
void borrow_init(){ //대출연결리스트 초기화 함수
	br_head=(borrow*)malloc(sizeof(borrow));
	br_tail=head;
	br_head->next=NULL;	
}
                              
int confirm_stnum( ){  // 존재하는 학번인지 확인하는 함수
	borrow *cf_node;
	br_tail->next=cf_node;

	while(1){
		if(cf_node->num == member->stnum )
			break;
		tail->next=member->next;
		member=tail->next;
		tail=member;
		if( tail  == NULL){
			printf("존재하지 않는 학번입니다.");
			return 3;
		}
	}
	return 0;
}

int confirm_isbn(){  //존재하는 isbn인지 확인하는 함수
	borrow* cf_node;
	br_tail->next=cf_node;
	Book* cf_isbn;
	Book_tmp->next= cf_isbn;
	while(1){
		if(cf_node->isbn == cf_isbn->Book_ISBN )
			break;
		Book_tmp->next=cf_isbn->next;
		cf_isbn=Book_tmp->next;
		Book_tmp=cf_isbn;
		if( Book_tmp==NULL){
			printf("존재하지 않는 isbn 입니다.");
			return 4;
		}
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
	scanf("%d", &new_node->num);
	a=confirm_stnum();
	if (a==3)
		return;

	int b;
	printf("  ISBN: ");
	scanf("%s", new_node->isbn);	
	b=confirm_isbn();
	if (b==4)
		return;
}

void save_borrow(){  //대출정보 저장
	FILE* brfp=fopen("borrow.txt","w");

	while(1){  //borrow연결리스트에 있는 정보탐색
		borrow *tmp=(borrow*)malloc(sizeof(borrow));
		br_tail->next=tmp;
		if (tail==NULL)
			break;
		fprintf(brfp, "%d %s\n", &tmp->num, tmp->isbn);
		br_tail->next=tmp->next;
		tmp=br_tail->next;
		br_tail=tmp;
	}
	fclose(brfp);
}

void delete_borrow(){	//도서반납->대출연결리스트에서 삭제
	borrow* node=(borrow *)malloc(sizeof(borrow));
	borrow* delnode=br_tail->next;
	int a,b;
	printf("학번 : ");
	scanf("%d",&node->num);
	a=confirm_stnum();  //존재하는 학번인지 확인
	if (a==3)
		return;

	printf("ISBN : ");
	scanf("%s", node->isbn);
	b=confirm_isbn();   //존재하는 isbn인지 확인
	if (b==4)
		return;
	
	while(1){  //삭제할 노드 탐색
	if(int strcmp(node->num,delnode->num) == 0 && strcmp(node->isbn, delnode->isbn)==0){
		br_tail=delnode->next;//노드삭제
		free(delnode);
		printf("반납되었습니다.");
		break;
	}
	else if (br_tail->next==NULL){
		printf("대출 정보를 찾을 수 없습니다.");
		break;
	}
	else{
		br_tail->next=delnode->next;
        delnode=br_tail->next;
        tail=delnode;
	}
	}
}

/*
char find_mylist(){  //학번으로 내 대여목록 찾은 후 isbn반환
	int stnum;
	scanf("%d",stnum);
	borrow *my_list=(borrow *)malloc(sizeof(borrow));

	while (br_tail->next == NULL){

	if (stnum == my_list->num){
		printf("%s\n",my_list.isbn);//책 정보 출력-도서연결리스트
		my_list=br_tail->next;
		br_tail=my_list;
	}
	else if (stnum != my_list.num){
		my_list=br_tail->next;
		br_tail=my_list;
		}
	}
}
*/

int main() {
	borrow_init();
	confirm_stnum;
	confirm_isbn;
	add_borrowlist();
	save_borrow();
	delete_borrow();
}
