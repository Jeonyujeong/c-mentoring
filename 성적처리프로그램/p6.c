#include <stdio.h>
#include <stdlib.h>

typedef struct list{
	struct list *next;
	int korean;
	int english;
	int math;
	int total;
	int ave;
	char name[20];
} list;

int count=1;

void grade(list *p_head, list *p_cur){
	list *node=(list*)malloc(sizeof(list));
	
	printf("%d 번째 학생 이름 : \n", count);
	scanf("%s", node->name);
	printf(" 국어 점수 : \n");
	scanf("%d", &node -> korean);
	printf("영어 점수 : ");
	scanf("%d", &node->english);
	printf("수학 점수 : ");
	scanf("%d", &node->math);

	node->total = node->korean + node->english + node->math;
	count++;

	list *front = NULL;//앞 노드
	list *back = NULL;

	if (*p_head == NULL) {
		*p_head = node;
		*p_cur = p_head;
		(*p_cur)->next = NULL;
	}
	else if (back == *p_head){
		node->next - *p_head;
		*p_head=node;
	}
	else {
	node->next = front->next;
	front->next = node;
	}
}


void print(list *p_head )
{
	printf("--------------------------------\n");
	printf(" 이름  국어 영어 수학 총점 평균 등수\n");
	printf("--------------------------------\n");

	list *node = *p_head;
	int rank=1;
	while (node != NULL){
		printf("%s  %d  %d  %d  %d  %d등\n", node->name, node->korean, node->english, node->math, node->total, node->total/3, rank);
		rank++;
		node = node->next;
	}
}

void remove(list *head)
{
	list *tmp;
		while (head != NULL){
			tmp=head;
			head= head->node;
			free(tmp);
		}
}

int main()
	list *head = NULL, *cur = NULL;
	int menu;

	while (1){
		printf("[Menu]\n");
		printf("1. 성적 입력\n2. 성적 확인\n3. 종료\n");
		printf("--------------\n");
		printf("선택 ( 1 ~ 3 ) : ");
		scanf("%d", menu);

		if (menu==1) grade(&head, &cur);
		else if (menu==2) print(&head);
		else if (menu==3) break;
	}
remove(head);
}

