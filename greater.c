
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int val;
	struct node * next;
	struct node * prev;
};
void insert(struct node**,int );
int greater(struct node*, struct node*);
void del(struct node**);
int main()
{
	struct node *a,*b;int flag0=0,flag1=0,g;//flag0 for showing which number to insert to, flag1 to take care of stray zeros
		a=NULL;
		b=NULL;
	char c;
	while((c=fgetc(stdin))!=EOF)
	{
	if(c==' '){
		flag0=1;
		flag1=0;
		}
	else if(c=='\n')
	{	
		g=greater(a,b);
		printf("%d\n",g);
		flag0=0;
		flag1=0;
		
		del(&a);
		del(&b);//free memory
	}
    else
	{
		if(c!=48)//first number that is not zero
			flag1=1;
		if(flag1==1)
		{
			if(flag0==0)
			insert(&a,c);
			else
			insert(&b,c);
	}}	
    }

return 0;



}

void insert(struct node **h,int n)
{
	struct node *ptr=(struct node*)malloc(sizeof(struct node));
	ptr->val=n;
	ptr->next=*h;
	if(*h!=NULL)
	(*h)->prev=ptr;
	*h=ptr;
	(*h)->prev=NULL;
	
	
}
int greater(struct node *a, struct node *b)
{

	while(a!=NULL||b!=NULL)
	{
		if(b==NULL)//longer list equals greater number since 0s are removed
			return 1;
		if(a==NULL)
			return 0;
		if((a->next==NULL)&&(b->next==NULL))
			break;
		a=a->next;
		b=b->next;
		
	}
	do//list stores LSD at head, MSD at end back traversal on equality does the comparison correcty
	{
		if((a->val)>(b->val))
		return 1;
		else if((a->val)<(b->val))
		return 0;
	   else{
		   b=b->prev;
		   a=a->prev;
	}}while(a!=NULL);//equal numbers
	return 1;
	
	
	
}
void del(struct node **a)
{
	struct node *ptr;
	while(*a!=NULL)
	{
		ptr=*a;
		*a=(*a)->next;
		free(ptr);
	
	}
	

}
