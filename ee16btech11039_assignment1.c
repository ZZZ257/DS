
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int val;
	struct node * next;
	struct node * prev;
};

int convert (char ch)
{
int a=ch-48;
return a;	
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
void sum(struct node *a, struct node *b,struct node **y)
{
	int s,c=0;
	while(a!=NULL||b!=NULL)
	{
		if(b==NULL)
		{
			c+=a->val;
			s=c%10;
			c=c/10;
			insert(y,s);
			a=a->next;
		}
		else if(a==NULL)
		{
			c+=b->val;
			s=c%10;
			c=c/10;
			insert(y,s);
			b=b->next;
			
		}
		else{
			
			c+=a->val+b->val;
			s=c%10;
			c=c/10;
			insert(y,s);
			
			a=a->next;
			b=b->next;
			
		}
		
	}
		insert(y,c);
	
	
	
	
}

void display(struct node *a)
{
	int k=0;
	while(a!=NULL)
	{
	if((k==0)&&((a->val)!=0))
		k=1;	
	if(k==1){	
	printf("%d",a->val);
	}
	a=a->next;
	}
	printf("\n");
	
	
	
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
int main()
{
	struct node *a,*b,*x;int k=0;
	
	
		x=NULL;
		a=NULL;
		b=NULL;
	char c;
	while((c=fgetc(stdin))!=EOF)
	{
	if(c==' ')
		k=1;
	else if(c=='\n')
	{	
		sum(a,b,&x);
		k=0;
		
		display(x);
		del(&a);
		del(&b);
		del(&x);
		
	}
    else
	{
		if(k==0)
		insert(&a,convert(c));
		else
		insert(&b,convert(c));
	}	
    }

return 0;



}
