#include <stdio.h>
#include <malloc.h>

typedef struct Node{
	char name[100];
	int kor;
	int eng;
	int math;
	Node *next;
}Node;

int main(){
	Node *head=(Node *)malloc(sizeof(Node));
	head->next=NULL;
	
	
	Node *tmp=head;
	while(1){
		
	
	printf("[ Menu ]\n");
	printf("1. 성적 입력\n2. 성적 확인\n3. 종료\n\n");
	printf("---------------\n선택 { 1 ~ 3 } : ");
	int num;
	scanf("%d",&num);
	
	int sum=1;
	
	if(num==1){

		Node *q=(Node *)malloc(sizeof(Node));
		
		q->next=NULL;
	printf("%d 번째 학생 이름 : ",sum);	
		scanf("%s",&q->name);
		printf("국어 점수 : ");
		scanf("%d",&q->kor);
		printf("영어 점수 : ");
		scanf("%d",&q->eng);
		printf("수학 점수 : ");
		scanf("%d",&q->math);
		
		tmp->next=q;
		tmp=tmp->next;
		
		sum++;
		continue;
	}else if(num==2){
		Node *qq=head->next;
		printf("--------------------------------\n");
		printf("  이름  국어 영어 수학 총점 평균\n");
		printf("--------------------------------\n");
		while(qq!=NULL){
			int Sum=qq->kor+qq->eng+qq->math;
			printf("%s  %d   %d   %d   %d   %d\n",qq->name,qq->kor,qq->eng,qq->math,Sum,Sum/3);
			qq=qq->next;
			
		}
		
		continue;
		
	}else{
		return 0;
	}
	
	
}
	
}
