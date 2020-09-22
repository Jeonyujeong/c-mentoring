#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "student.h"

typedef struct borrow{
	int num;
	char isbn[10];
	struct borrow* next;

}borrow;

borrow* stHead;
borrow* tail;

void init(){
	stHead=(borrow*)malloc(sizeof(borrow));
	tail=stHead;
	stHead->next=NULL;
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
