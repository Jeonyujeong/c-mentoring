#include <stdio.h>
#include <malloc.h>

typedef struct Node{
	char name[100];
	int kor;
	int eng;
	int math;
	int sum;
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
		q->sum=q->kor+q->eng+q->math;
	
		
		Node *add=head;
		if(add->next==NULL){
			head->next=q;
		}else{
			Node *add_back=add->next;
			
			
			while(add_back->sum>q->sum&&add_back->next!=NULL){
				add=add_back;
				add_back=add_back->next;
			}
			
			if(add_back->sum>q->sum){
				add_back->next=q;
			}else{
			
			q->next=add_back;
			add->next=q;
		}
		}
		
		
		sum++;
		continue;
	}else if(num==2){
		Node *qq=head->next;
		int u=1;
		printf("------------------------------------\n");
		printf("  �̸�  ���� ���� ���� ���� ��� ���\n");
		printf("------------------------------------\n");
		while(qq!=NULL){
			
			printf("  %5s%3d%5d%5d%5d%4d%4d\n",qq->name,qq->kor,qq->eng,qq->math,qq->sum,qq->sum/3,u);
			qq=qq->next;
			u++;
		}
		
		continue;
		
	}else{
		return 0;
	}
	
	
}
	
}
