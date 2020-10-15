typedef struct borrow{
     char num[20];
     char isbn[20];
//int -> char 형 변환함
     struct borrow* next;
 }borrow;
 
 borrow* br_head;
 borrow* br_tail;
 
void borrow_init();
int confirm_stnum();
int confirm_isbn();
void add_borrowlist();
void save_borrow();
void delete_borrow();
