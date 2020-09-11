#include <stdio.h>
#include <stdlib.h>

typedef struct borrow{
	int num;
	char isbn[10];
	struct borrow* next;

}borrow;

borrow* head;
borrow* tail;

void init(){
	head=(borrow*)malloc(sizeof(borrow));
	tail=head;
	head->next=NULL;
}

void add(){
	borrow *new_node= (borrow*)malloc(sizeof(borrow));

	printf("[ 도서 대여 ]\n");
	printf("  학번: ");
	scanf("%d", &new_node->num);
	printf("  ISBN: ");
	scanf("%s", new_node->isbn);
	tail->next = new_node;
	tail= new_node;
	tail->next = NULL;

}

void save(){
	FILE* fp=fopen("borrow.txt","w");

	borrow *tmp=(borrow*)malloc(sizeof(borrow));

	fprintf(fp, "%d %s\n", tmp->num, tmp->isbn);
	fclose(fp);
}

int main() {

	init();
	add();
	save();
}
