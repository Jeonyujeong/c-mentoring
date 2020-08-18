#include <stdio.h>
int main(void)
{
	int num1=10;
	int num2=20;
	int *ptr1=&num1;
	int *ptr2=&num2;

	(*ptr1)+=10;
	(*ptr2)-=10;
	
	int *tmp;
	*tmp=* ptr1;
	*ptr1=*ptr2;
	*ptr2=*tmp;
	
	printf("%d %d \n", &ptr1, &ptr2);
	return 0;
}
