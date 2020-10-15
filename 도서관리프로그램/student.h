


int withdraw();
void signUp();
void logIn();
void SuccessLogin_menu();
void student_free();
void MainMenu();
int FailLogin_menu();
int borrow_confirm();
void myBorrow_list();
void Update_studentData();
void st_InitNode();
void Import_studentData();

typedef struct student{
	struct student* next;

	char stnum[20];
	char passward[20];
	char name[20];
}student;

student* SThead;
student* member;
