#include <stdio.h>



int main(){
	
	
	int arr[45]={};
	arr[0]=1;
	arr[1]=1;
	int n;
	scanf("%d",&n);
	
	for(int i=2;i<n;i++){
			arr[i]=arr[i-1]+arr[i-2];
			
		}
	printf("%d",arr[n-1]);
	
}
