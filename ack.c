#include<stdio.h>
#include<stdlib.h>
int A(int m,int n)
{
	if(m==0)
		return (n+1);
	if(n==0)
		return (A(m-1,1));
		return(A(m-1,A(m,n-1)));
	
	
}
int main()
{
	int b;
	b=A(3,11);
	printf("%d",b);
	
}