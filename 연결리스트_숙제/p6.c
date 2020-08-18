#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct node *p_next;
	int korean;
	int english;
	int math;
	int total;
	char name[20];
} Node;

int main()
{
	Node *p_head=Null, *p_next=Null;

	int menu;
	while(1){
		printf("[Menu]\n");
		printf(" 1. 성적 입력\n");
		printf(" 2. 성적 확인\n");
		printf(" 3. 종료\n");
		printd("-------------------------\n");
		printf("선택 ( 1 ~ 3 ) : ");
		scanf("%d", &menu);

		if (menu==1)
			grade (&p_head, &p  ,&p);
		else if (menu==2)
			print (&p_head);
		else if (menu==3)
			break;
	}
}

void grade(Node *head, Node *
		{
		Node *p_node=(Node*)malloc(sizeof(Node));

		printf("%d 번째 학생 이름 : \n", * );
		scanf("%s", p_node->name);
		printf("% 국어 점수 : \n");
		scanf("%d", &p_node -> korean);

		printf("영어 점수 : ");
		scanf("%d", &p_node->enlish);
		printf("수학 점수 : ");
		scanf("%d", &p_node->math);
		}		

void print(Node *  )
{
	printf("--------------------------------\n");
	printf(" 이름  국어 영어 수학 총점 평균 등수\n");
	printf("--------------------------------\n");

	Node *p_node 
	}

void remove(Node *p_head)  //메모리 해제 free
{
	Node *p_node;
	while (p_heaf != NULL{
			p_node = p_head;
			p_head = p_head->p_next;
			free(p_node);
			}
}

