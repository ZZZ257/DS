#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
/*
void display(struct node *a);
int convert (char ch);
void insert(struct node **h,int n);
struct node * sum(struct node *a, struct node *b);
void del(struct node *a);
*/
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

void del(struct node *a)
{
	struct node *ptr;
	while(a!=NULL)
	{
		ptr=a;
		a=a->next;
		free(ptr);
		printf("%d",ptr->val);
	}
	

}

void main()
{
	struct node *a[100],*b[100],*x[100];int i,k=0;
	for (i=0;i<100;i++)
	{
		x[i]=NULL;
		a[i]=NULL;
		b[i]=NULL;
	}char c;i=0;
	while((c=fgetc(stdin))!='a')
	{
	if(c==' ')
		k=1;
	else if(c=='\n')
	{	
		sum(a[i],b[i],&x[i]);
		k=0;
		
		display(x[i]);
		del(a[i]);
		del(b[i]);
		display(a[i]);
		i++;
	}
    else
	{
		if(k==0)
		insert(&a[i],convert(c));
		else
		insert(&b[i],convert(c));
	}	
    }
for (i=0;i<100;i++)
{   if(x[i]!=NULL)
	display(x[i]);
		del(x[i]);
}
}


