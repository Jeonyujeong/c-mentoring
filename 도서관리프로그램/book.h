typedef struct Book{
	char Book_name[30];
	char Book_company[30];
	char Book_ISBN[20];
	char Book_author[20];
	char Book_borrow; 
	struct Book *next;
	
}Book;

Book *Book_head;
Book *Book_tmp;
Book *ttmp;
Book *ttmp_back;
Book *q;

void Login();
void bk_init();
void Load_list_to_file();
int Admin_mode();
void add_book();
void remove_book();
void borrow_book();
void return_book();
void Search_book_name();
int Find_book();
void Book_information(Book *);
void Admin();
void return_book();
Book* ISBN_cmp();
void Find_author();
