#include<stdio.h>
#include<stdlib.h>
struct number
{
	int val;
	struct number * next;
	struct number * prev;
};
void insert(struct number **h,int n)
{
	struct number *ptr=(struct number*)malloc(sizeof(struct number));
	ptr->val=n;
	ptr->next=*h;
	if(*h!=NULL)
	(*h)->prev=ptr;
	*h=ptr;
	(*h)->prev=NULL;
	
	

}
void copy(struct number **n,struct number *a)
{
	int x;
	while(a->next!=NULL)
		a=a->next;
	while(a!=NULL)
	{
		x=a->val;
		insert(n,a->val);
		a=a->prev;
	}
}
void display(struct number *a)
{
	int k=0;
	while(a!=NULL)
	{
	if((k==0)&&((a->val)!=0))
		k=1;	
	if(k==1){	
	printf("%c",a->val);
	}
	a=a->next;
	}
	printf("\n");
	
	
	
}
int main()
{
	struct number *a=NULL,*b=NULL;
	insert(&a,49);
	insert(&a,49);
	insert(&a,49);

	display(a);
	copy(&b,a);
	
	display(b);
	}