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
	printf("1. ���� �Է�\n2. ���� Ȯ��\n3. ����\n\n");
	printf("---------------\n���� { 1 ~ 3 } : ");
	int num;
	scanf("%d",&num);
	
	int sum=1;
	
	if(num==1){

		Node *q=(Node *)malloc(sizeof(Node));
		
		q->next=NULL;
	printf("%d ��° �л� �̸� : ",sum);	
		scanf("%s",&q->name);
		printf("���� ���� : ");
		scanf("%d",&q->kor);
		printf("���� ���� : ");
		scanf("%d",&q->eng);
		printf("���� ���� : ");
		scanf("%d",&q->math);
		
		tmp->next=q;
		tmp=tmp->next;
		
		sum++;
		continue;
	}else if(num==2){
		Node *qq=head->next;
		printf("--------------------------------\n");
		printf("  �̸�  ���� ���� ���� ���� ���\n");
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
