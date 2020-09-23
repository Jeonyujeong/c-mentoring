typedef struct borrow{
     int num[20];
     int isbn[20];
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
