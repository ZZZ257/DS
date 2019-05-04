
#include<stdio.h>
#include<stdlib.h>

struct number
{
	int val;
	struct number * next;
	struct number * prev;
};

struct node
{
	struct number * var;
	struct node * left;
	struct node * parent;
	struct node * right;
};
void deltree(struct node **);
void display(struct number *);
void copy(struct number **,struct number * );
void search(struct node *,struct number *);
void traverse(struct node *);
void ins(struct number**,int );
void insert(struct node**,struct number* );
int cmp(struct number*, struct number*);
void del(struct number**);
int main()
{
	struct number *a=NULL,*b=NULL;int flag0=0,flag1=0;//flag0 for showing insert , search or traversal, flag1 to take care of stray zeros
		struct node *root=NULL;
		
		
	char c;
	while((c=fgetc(stdin))!=EOF)
	{	
		if(c=='S')
			flag0=1;
		else if(c=='N'){// new tree is inserted
			deltree(&root);
			flag0=0;
		}
		else if(c=='P')
			flag0=-1;
			else if(c==' ')
		{
			
			
			if((flag1==0)&&(flag0==2))
				ins(&a,'0');//insert zero to list if entire string was a set of zeroes without a non zero number(insert removes all zeros before a nonzero number)
			
		
			if(flag0==2)// a number is inserted after an 'N'
			{
				insert(&root,a);
	            del(&a);     
			}
			if(flag0==0)//space after an N, flag0=2 indicates that next thing bust be a number
				flag0=2;
			
			flag1=0;
		}
	else if(c=='\n')
	{	
		
		switch(flag0)
		{
			case -1://traversal
			traverse(root);
				printf("\n");
				break;
			
			case 1://search
				if(flag1==0)
				ins(&a,'0');	
				search(root,a);
				del(&a);
				break;
			
			case 2://last number
				if(flag1==0)
				ins(&a,'0');
				insert(&root,a);
				del(&a);
		}
		flag1=0;
		
		//free memory
	}
    else
	{
		
		if((c!=48))//first number that is not zero
			flag1=1;
			
		if(flag1==1)
		{
			
				ins(&a,c);
			
	}
	
	}	
    }

return 0;



}
void traverse(struct node *ptr)//preorder traversal by recursion
{
	if(ptr!=NULL)
	{	
		display(ptr->var);
		traverse(ptr->left);
		traverse(ptr->right);
	}
}
void insert(struct node **root,struct number *n)
{
	struct node *ptr1,*ptr2;
	ptr1=*root;
	int k=0;
	if(*root==NULL)//root of tree
	{
	*root=(struct node*)malloc(sizeof(struct node));
    (*root)->var=NULL;	
	copy(&((*root)->var),n);	
	(*root)->parent=NULL;
	(*root)->left=NULL;
	(*root)->right=NULL;

	
	}
	
	else
	{//insertion to bst
		while (ptr1!=NULL)
		{
			
			ptr2=ptr1;
			if(cmp(ptr1->var,n)==0)//ptr1->var=n
				return;
			else if(cmp(ptr1->var,n)==1)//ptr1->var>n
			{
			
				ptr1=ptr1->left;
				k=-1;
			}
			else//ptr1->var<n
			{
				k=1;
				ptr1=ptr1->right;		
			}
			
		}
		
		ptr1=(struct node*)malloc(sizeof(struct node));
		ptr1->var=NULL;
		copy(&(ptr1->var),n);
		ptr1->parent=ptr2;
		if(k==-1)
			ptr2->left=ptr1;
		else
			ptr2->right=ptr1;
		ptr1->left=NULL;
		ptr1->right=NULL;
	}
}
void search(struct node *x,struct number *n)
{
	int k=0;
	struct number * b=NULL;
	while (x!=NULL)
	{
		if(cmp(x->var,n)==0)
		{
			k=1;
			break;
		}
		else if (cmp(x->var,n)==1)
		{
			ins(&b,'0');
			x=x->left;
		}
		else
		{ 
			x=x->right;
			ins(&b,'1');
		}
	}
	if(k==0)
		printf("-1");
	else
		display(b);
		del(&b);
	printf("\n");
	
}
void display(struct number *a)
{
	if(a!=NULL)// if a==NULL nothing is printed
	{
	while(a->next!=NULL)//moving to end
	{	
	a=a->next;
	}
	while(a!=NULL)//miving back from the end
	{
	printf("%c",a->val);	
	a=a->prev;	
	}printf(" ");
	
	
	}
}
void copy(struct number **n,struct number *a)
{
	
	while(a->next!=NULL)
		a=a->next;
	while(a!=NULL)
	{
		
		ins(n,a->val);
		a=a->prev;
	}
}

void ins(struct number **h,int n)
{
	struct number *ptr=(struct number*)malloc(sizeof(struct number));
	ptr->val=n;
	ptr->next=*h;
	if(*h!=NULL)
	(*h)->prev=ptr;
	*h=ptr;
	(*h)->prev=NULL;
	
	
}
int cmp(struct number *a, struct number *b)
{

	while(a!=NULL||b!=NULL)
	{
		if(b==NULL)//longer list equals biger number since 0s are removed
			return 1;
		if(a==NULL)
			return (-1);
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
		return (-1);
	   else{
		   b=b->prev;
		   a=a->prev;
	}}while(a!=NULL);//equal numbers
	return 0;
	
	
	
}
void deltree(struct node **a)
{//free entire tree
	if((*a)!=NULL)
	{
		deltree(&((*a)->left));
		deltree(&((*a)->right));
		del(&((*a)->var));
		free(*a);
		*a =NULL;
		
		
	}
	
	
}
void del(struct number **a)
{//free entire number
	struct number *ptr;
	while(*a!=NULL)
	{
		ptr=*a;
		*a=(*a)->next;
		free(ptr);
		
	}
	

}
