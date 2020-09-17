#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "book.h"


#define Book_name_size 100
#define Book_company_size 30
#define Book_ISBN_size 20
#define Book_author_size 20



void Login(){           //�α���â �Լ�

	char Adminnum[]="admin";
	char Adminpassword[]="admin";
	char Num[20];
	char Password[20];

	printf("\n[�α���]\n");
	printf("�й�:");
	scanf("%s",Num);
	printf("���й�ȣ:");
	scanf("%s",Password);

	if(strcmp(Adminnum,Num)==0&&strcmp(Adminpassword,Password)==0){
		Admin();
	}else{
		//�л� �α��� �������� Ȯ��...
		printf("�α��ο� �����߽��ϴ�.\n");
	}

}


/*
typedef struct Book{      //���� ���� ��ũ�帮��Ʈ
	char Book_name[Book_name_size];
	char Book_company[Book_company_size];
	char Book_ISBN[Book_ISBN_size];
	char Book_author[Book_author_size];
	char Book_borrow;
	struct Book *next;

}Book;

Book *Book_head;
Book *Book_tmp; //�� �� å ��ġ
Book *ttmp;
Book *ttmp_back;

*/

void bk_init(){                          // book ����Ʈ �� ó���κ� ������ �Լ�

FILE* fp=fopen("bk.txt","w");
	Book_head=(Book *)malloc(sizeof(Book));

	Book_head->next=NULL;
	Book_tmp=Book_head;
	fclose(fp);
}



int Admin_mode(){                      //������ ���� ���� �Լ� ,���� �� ����
	int choice;
	printf("\n[������ ����]\n");
	printf("1. ���� ����\n");
	printf("2. ���� ����\n");
	printf("3. ���� �뿩\n");
	printf("4. ���� �ݳ�\n");
	printf("5. ���� �˻�\n");
	printf("6. ȸ�� ����\n");
	printf("7. �α׾ƿ�\n");
	printf("8.���α׷� ����\n");

	scanf("%d",&choice);
	return choice;
}



void add_book(){                 //���� ���� �Լ�
	Book *p=(Book *)malloc(sizeof(Book));

	printf("[ ���� ���� ]\n");
	printf("������:");
	getchar();
	fgets(p->Book_name,Book_name_size,stdin);
	Erase_enter(p->Book_name);
	printf("���ǻ�:");
	fgets(p->Book_company,Book_name_size,stdin);
	Erase_enter(p->Book_company);
	printf("���ڸ�:");
	fgets(p->Book_author,Book_name_size,stdin);
	Erase_enter(p->Book_author);
	printf("ISBN:");
	fgets(p->Book_ISBN,Book_name_size,stdin);
	Erase_enter(p->Book_ISBN);

	printf("���Ⱑ�� ����(y/n):");
	scanf("%c",&p->Book_borrow);
	getchar();
	while(p->Book_borrow!='y'&&p->Book_borrow!='n'){
		printf("'y'�� 'n'�� �ϳ��� �Է��� �ֽʽÿ� :");
		scanf("%c",&p->Book_borrow);
		getchar();

	}
	p->next=NULL;

	Book_tmp->next=p;
	Book_tmp=Book_tmp->next;

	/*FILE* fp=fopen("bk.txt","w");
	fprintf(fp,"%s %s %s %s %c\n",p->Book_name,p->Book_company,p->Book_author,p->Book_ISBN,p->Book_borrow);
	fclose(fp);
	*/
}

void remove_book(){              // ���� ���� �Լ�
	char name[Book_name_size];
	printf("������:");
	scanf("%s",name);
	ttmp=Book_head->next;
	ttmp_back=Book_head;
	while(ttmp!=NULL&&strcmp(ttmp->Book_name,name)!=0){
		ttmp_back=ttmp;
		ttmp=ttmp->next;
	}
	if(ttmp==NULL){
		printf("%s�� ������ ã�� �� �����ϴ�.\n",name);
	}else{
		if(ttmp->Book_borrow=='n'){
			printf("�������� å�� ������ �Ұ����մϴ�.\n");
		}else{

			ttmp_back->next=ttmp->next;
			free(ttmp);
			printf("������ �Ϸ��Ǿ����ϴ�.\n");
			Load_list_to_file();
		}


	}
}

void borrow_book(){        //���� �뿩 �Լ�
char student[10];
char ISBN[Book_ISBN_size];
	printf("[�����뿩]\n");
	printf("�й� :");

	scanf("%s",student);
	printf("ISBN :");
	 scanf("%s",ISBN);
	 //�л� ����Ʈ �̿��ؼ�...(�й��� �´� �л� ������ ��������(�л� ���Ͽ� å�� �߰����ش�)
	 ttmp=Book_head->next;
	 while(ttmp!=NULL&&strcmp(ttmp->Book_ISBN,ISBN)!=0){
		 ttmp=ttmp->next;
	 }
	 if(ttmp==NULL){
	 	printf("�������� �ʴ� �����Դϴ�.\n") ;
	 }else{

	 	if(strcmp(ttmp->Book_ISBN,ISBN)==0){
	 		if(ttmp->Book_borrow=='n'){
	 			printf("�̹� ������ �����Դϴ�.\n");

			 }else{
			 	printf("'%s'å�� �����Ǿ����ϴ�.\n",ttmp->Book_name);
			 	ttmp->Book_borrow='n';
			 	Load_list_to_file();

			 }

		 }
	 }

}

Book* ISBN_cmp(char ISBN[Book_ISBN_size]){  //isbn�� �޾� �����帮��Ʈ �ȿ��� �����ؼ� book���� �ּ� ��ȯ�ϴ� �Լ�

	ttmp=Book_head->next;

	while(ttmp!=NULL&&strcmp(ttmp->Book_ISBN,ISBN)!=0){
		 ttmp=ttmp->next;
	}
	return ttmp;
}

void return_book(){      //���� �ݳ� �Լ�

	char ISBN[Book_ISBN_size];
	printf("ISBN:");
	scanf("%s",ISBN);

	q=ISBN_cmp(ISBN);

	if(q==NULL){
	 	printf("�������� �ʴ� �����Դϴ�.\n") ;
	}else{

	 	if(strcmp(q->Book_ISBN,ISBN)==0){
	 		if(ttmp->Book_borrow=='y'){
	 			printf("�̹� �ݳ��� �����Դϴ�.\n");

			 }else{
			 	printf("'%s'å�� �ݳ��Ǿ����ϴ�.\n",q->Book_name);
			 	q->Book_borrow='y';
			 	Load_list_to_file();

			 }

		 }
	 }

}

void Load_list_to_file(){   //����Ʈ���� ���Ϸ� �Է����ִ� �Լ�
	FILE* fp= fopen("bk.txt","w");
	ttmp=Book_head->next;
	while(ttmp!=NULL){
		fprintf(fp,"%s %s %s %s %c",ttmp->Book_name,ttmp->Book_company,ttmp->Book_author,ttmp->Book_ISBN,ttmp->Book_borrow);
		ttmp=Book_tmp->next;
	}
	fclose(fp);
}


void Book_load(){                  //���Ͽ��� ��ũ�帮��Ʈ�� ������ �Լ�->���� ���غ�
	char name[Book_name_size];
	char company[Book_company_size];
	char ISBN[Book_ISBN_size];
	char author[Book_author_size];
	char borrow;


	FILE* fp=fopen("bk.txt","r");
	int ret=0;

	while(1){

		Book *q=(Book *)malloc(sizeof(Book));
		q->next=NULL;

		ret=fscanf(fp,"%s %s %s %s %c",name,company,author,ISBN,&borrow);

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


int Find_book(){        //[�����˻�]â  ,��ȣ ����

	int num;
	while(1){

	printf("\n[�����˻�]\n");
	printf("1. ������ �˻�\n");
	printf("2. ���ǻ� �˻�\n");
	printf("3. ISBN �˻�\n");
	printf("4. ���ڸ� �˻�\n");
	printf("5. ��ü �˻�\n");
	printf("6. ���� �޴�\n");
	scanf("%d",&num);

	if(num==1){
		Search_book_name();
	}else if(num==2){
		Search_book_company();
	}else if(num==3){
		char isbn[Book_ISBN_size];

		printf("ISBN: ");
		scanf("%s",isbn);
		q=ISBN_cmp(isbn);

		if(q==NULL){
			printf("�������� �ʴ� �����Դϴ�.\n");
		}else{
			Book_information(q);
		}
	}else if(num==4){
		Search_book_author();

	}else if(num==5){

	}else if(num==6){
		break;
	}else{
		printf("1~6������ ���� �Է��� �ֽʽÿ�\n");
	}
	}
}

void Search_book_author(){   //���ڸ� ã���ִ� �Լ�

	char author[Book_author_size];
	printf("���ڸ� :");
	getchar();
	fgets(author,Book_author_size,stdin);
	Erase_enter(author);

	ttmp=Book_head->next;
	int nu=0;

	while(ttmp!=NULL){
		if(Find_word(author,ttmp->Book_author)==1){
			Book_information(ttmp);
			nu++;
		}
		ttmp_back=ttmp;
		ttmp=ttmp->next;
	}

	if(nu==0){
		printf("���ڸ��� %s�� ������ ã�� �� �����ϴ�.\n",author);
	}else{
		printf("\n�� %d���� å�� �˻��Ǿ����ϴ�.\n",nu);
	}
}

void Search_book_company(){        //���ǻ� ã�� �Լ�

	char company[Book_company_size];
	printf("���ǻ��� :");
	getchar();
	fgets(company,Book_company_size,stdin);
	Erase_enter(company);

	ttmp=Book_head->next;
	int nu=0;

	while(ttmp!=NULL){
		if(Find_word(company,ttmp->Book_company)==1){
			Book_information(ttmp);
			nu++;
		}
		ttmp_back=ttmp;
		ttmp=ttmp->next;
	}

	if(nu==0){
		printf("���ǻ簡  %s�� ������ ã�� �� �����ϴ�.\n",company);
	}else{
		printf("\n�� %d���� å�� �˻��Ǿ����ϴ�.\n",nu);
	}
}

void Book_information(Book *node){      //���� �ּҸ� �޾� ������ �� �������ִ� �Լ�

	printf("\n������ : %s\n",node->Book_name);
	printf("���ǻ� : %s\n",node->Book_company);
	printf("ISBN : %s\n",node->Book_ISBN);
	printf("���ڸ� : %s\n",node->Book_author);
	printf("���⿩�� : %c\n",node->Book_borrow);

}


void Erase_enter(char *s){  //���๮�� �����ִ� �Լ�
	s[strlen(s)-1]='\0';
}

void Search_book_name(){         //������ �˻� �Լ�
	char name[Book_name_size];
	printf("å�̸�: ");
	getchar();
	fgets(name,Book_name_size,stdin);
	Erase_enter(name);

	ttmp=Book_head->next;
	int nu=0;
	while(ttmp!=NULL){
		if(Find_word(name,ttmp->Book_name)==1){
			Book_information(ttmp);
			nu++;
		}
		ttmp_back=ttmp;
		ttmp=ttmp->next;
	}
	if(nu==0){
		printf("%s�� ������ ã�� �� �����ϴ�.\n",name);
	}else{
		printf("�� %d���� å�� �˻��Ǿ����ϴ�.\n",nu);
	}

}

int Find_word(char *a,char *b){       //�ܾ� ã�� �Լ�

	if(strstr(b,a)==NULL){
		return 0;
	}else{
		return 1;
	}

}

void books(){
	ttmp=Book_head->next;
	while(ttmp!=NULL){
		printf("%s %s %s %s %c\n",ttmp->Book_name,ttmp->Book_company,ttmp->Book_author,ttmp->Book_ISBN,ttmp->Book_borrow);
		ttmp=ttmp->next;

	}

}
void Admin(){     //�����ڸ���

		while(1){

	int c_num=0;
	c_num=Admin_mode();           ///���� �Է½� ���Ѽ��� ����...?

	if(c_num==1){
		add_book();
		Load_list_to_file();
	}else if(c_num==2){
		remove_book();

	}else if(c_num==3){
		borrow_book();
	}else if(c_num==4){
		return_book();
	}else if(c_num==5){
		Find_book();

	}else if(c_num==6){
		//ȿ���� �л� ���Ḯ��Ʈ �ҷ�����

	}else if(c_num==7){
	 //�� ó�� [������ ������]�� �̵�
	}else if(c_num==8){
		break;
	}else{
	  printf("1���� 8������ �� �� �ϳ��� �Է��� �ֽʽÿ�.\n");
	  fflush(stdin);
	}



}
}


int main(){

	bk_init();
	Login();


	return 0;
}
