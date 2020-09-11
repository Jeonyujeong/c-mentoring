exe : Manage_student.o borrow.o book.o
	gcc -o exe Manage_student.o borrow.o book.o

Manage_student.o : Manage_student.c
	gcc -c -o Manage_student.o Manage_student.c

borrow.o : borrow.c
	gcc -c -o borrow.o borrow.c

book.o : book.c
	gcc -c -o book.o book.c

clean:
	rm *.o exe
