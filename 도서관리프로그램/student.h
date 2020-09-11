typedef struct stNode{
	struct stNode* next;
	char stnum[20];
	char passward[20];
	char name[20];
}student;

student* head;
student* tail;
student* member;

void signUp();
void logIn();
void Freedata();
void node_print();
void st_InitNode();
void Import_studentData();
