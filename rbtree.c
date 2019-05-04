
#include<stdio.h>
#include<stdlib.h>

struct list
{
	int val;
	struct list *next;
};
struct node
{
	int var;
	int color;
	struct node * left;
	struct node * parent;
	struct node * right;
};
void blacken(struct node *,struct node **);
void fixinsert(struct node **, struct node *);
struct node * nil;
void lrot(struct node *, struct node **);
void rrot(struct node *, struct node **);
struct node * uncle(struct node * a);
void children(struct node * a);
void ins(struct list **,int );
void del(struct list **);
void display(struct list *);
struct node * succ(int, struct node *);
void delnode(struct node **, struct node *);
void deltree(struct node **);
struct node * search(struct node *,int, int);
void traverse(struct node *);
struct node * insert(struct node**,int );
void splice( struct node *,struct node **);
int main()
{
	nil=(struct node*)malloc(sizeof(struct node));
	nil->left=nil->right=nil->parent=NULL;
	nil->var=-1;
	nil->color=0;
	
	int a=0;int flag0=0;//flag0 for showing insert , search or traversal,adding element, removing element, successor, insert by preorder, rotate, find uncle, find children
		struct node *root=NULL;
		struct node *s;
	char c;
	while((c=fgetc(stdin))!=EOF)
	{	
		
		if(c=='+')//same as insertion but tree is not deleted
		    flag0=0;
		else if(c=='L')// left rotate
			flag0=5;
		else if(c=='R')// right rotate
			flag0=6;
		else if(c=='C')//children
			flag0=7;
		else if(c=='U')//uncle
			flag0=8;
		else if(c=='-')//delete
			flag0=3;
		else if(c=='>')//successor
			flag0=4;
		else if(c=='S')//search
			flag0=1;
		 	
		else if(c=='N'){// new tree is created and elements are inserted
			deltree(&root);
			flag0=0;
		}
		else if(c=='P')
			flag0=-1;
			else if(c==' ')
		{
			
			//insert zero to list if entire string was a set of zeroes without a non zero list(insert removes all zeros before a nonzero list)
			
		
			

			if(flag0==2)// a list is inserted after an 'N' or '+'
			{
				insert(&root,a);
	            a=0;     
			}
			if(flag0==0)//space after an N or a +, flag0=2 indicates that preceding string was a list
				flag0=2;
				if(flag0==10)
					flag0=9;
			
		}
	else if(c=='\n')
	{	
		
		switch(flag0)
		{
			
			case 5:
			s=search(root,a,0);
			lrot(s, &root);
			a=0;
			break;
			case 6:
			s=search(root,a,0);
			rrot(s,&root);
			a=0;
			break;
			case 7:
			s=search(root,a,0);
			children(s);
			a=0;
			break;
			case 8:
			s=search(root,a,0);
			s=uncle(s);
			if(s==NULL)
				printf("-1\n");
			else
				printf("%d\n",s->var);
			a=0;
			break;
			case -1://traversal	
			traverse(root);
				printf("\n");
				break;
			case 4://successor
				s=succ(a,root);
				if(s!=NULL)
				printf("%d",s->var);
				else
				printf("-1");
				printf("\n");
				a=0;
				break;
				
			case 3://deletion
			    s=search(root,a,0);
				if(s!=NULL);
				delnode(&root,s);
				a=0;
				break;
			case 1://search	
				search(root,a,1);
				a=0;
				break;
			
			case 2:
				insert(&root,a);
				a=0;
				break;
			
				
		}
		
		a=0;
		
	}
  else
	{
		
		a=(a*10)+c-48;
	
	}	
    }
deltree(&root);
return 0;



}
void traverse(struct node *ptr)//preorder traversal by recursion
{
	if(ptr!=nil)
	{	
		printf("%d ",ptr->var);	
		traverse(ptr->left);
		traverse(ptr->right);
	}
}
struct node * insert(struct node **root,int n)
{
	struct node *ptr1,*ptr2;
	ptr1=*root;
	int k=0;
	if(*root==NULL)//root of tree
	{
	*root=(struct node*)malloc(sizeof(struct node));	
	(*root)->var=n;	
	(*root)->parent=NULL;
	(*root)->left=nil;
	(*root)->right=nil;
	(*root)->color=0;
	fixinsert(root,*root);
	}
	
	else
	{//insertion to bst
		while (ptr1!=nil)
		{
			
			ptr2=ptr1;
			if(ptr1->var==n)
				return NULL;
			else if(ptr1->var>n)
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
		ptr1->var=n;
		ptr1->parent=ptr2;
		if(k==-1)
			ptr2->left=ptr1;
		else
			ptr2->right=ptr1;
		ptr1->left=nil;
		ptr1->right=nil;
		ptr1->color=1;
		fixinsert(root,ptr1);
		return ptr1;
		
	}
}
void fixinsert(struct node ** root, struct node * x)
{
	struct node * u;
	if(x==*root)
	{
		x->color=0;
		return;
	}
	else if(x->parent->color==0)
			return;
	else
	{
		u=uncle(x);
		if(u->color==1)
		{
			(x->parent->color)=0;
			(u->parent->color)=1;
			(u->color)=0;
			fixinsert(root,u->parent);
		}
		else if((x==x->parent->left)&&(u==x->parent->parent->right))
		{
			
			(x->parent->color)=0;
			(x->parent->parent->color)=1;
			rrot(x->parent->parent,root);
			
		}
		else if((x==x->parent->right)&&(u==x->parent->parent->left))
		{
			
		    (x->parent->color)=0;
			(x->parent->parent->color)=1;
			lrot(x->parent->parent,root);	
		}
		else if((x==x->parent->right)&&(u==x->parent->parent->right))
		{
			x=x->parent;
			lrot(x,root);
			fixinsert(root,x);
		}
		else
		{
			x=x->parent;
			rrot(x,root);
			fixinsert(root,x);
		}
		
	}
	
	
}
struct node * search(struct node *x,int n, int p)// p=0 indicates that address of node that contains list n must be returned p=1 indicates that path must printed 
{
	
	int k=0;
	struct list* b=NULL;
	while (x!=NULL)
	{
		if(x->var==n)
		{
			k=1;
			break;
		}
		else if ((x->var)>n)
		{
			ins(&b,0);
			x=x->left;
		}
		else
		{ 
			x=x->right;
			ins(&b,1);
		}
	}
	if(p==1)
	{
	if(k==0)
		printf("-1");
	else
		display(b);
		if(x->color==0)
		printf(" B");
		else
		printf(" R");
		del(&b);
	printf("\n");
	return NULL;
	}
	else
	{
		if(k==0)
		return NULL;
		else
		return x;
	}
		
		}



void deltree(struct node **a)
{//free entire tree
	if(((*a)!=NULL)&&((*a)!=nil))
	{
		deltree(&((*a)->left));
		deltree(&((*a)->right));
		free(*a);
		*a =NULL;
		
		
	}
	
	
}

struct node * succ(int a, struct node *y)
{
	
	int flag=0;
	if(y==NULL)
		return NULL;
	struct node *x=NULL;	
		
	
	while(y!=NULL)
		{
		if(a<(y->var))
			{
				
		
			if(x==NULL)
				x=y;
			else if((x->var)>(y->var))
				x=y;
				y=y->left;
			}
			else if(a>(y->var))
				y=y->right;
			else
			{
				flag=1;
				break;
			}
		}
	
	// node has a right child
	if((flag==1)){
		if((y->right!=nil))
	{ 	
		x=y;
		x=x->right;
		while((x->left)!=nil)
		x=x->left;
		
	}}
	return x;
}
void ins(struct list **h,int n)
{
	struct list *h1=*h,*ptr=(struct list*)malloc(sizeof(struct list));
	ptr->val=n;
	if(h1!=NULL)
	{
	while((h1->next)!=NULL)
		h1=h1->next;
	h1->next=ptr;
	}
	else
		*h=ptr;
	ptr->next=NULL;
		
}

void del(struct list **a)
{//free entire list
	struct list *ptr;
	while(*a!=NULL)
	{
		ptr=*a;
		*a=(*a)->next;
		free(ptr);	
	}
}
void display(struct list *a)
{
	// if a==NULL nothing is printed
	
	while(a!=NULL)
	{	
	printf("%d",a->val);
	a=a->next;
	}
}

void children(struct node * a)
{
	if(a==NULL||a==nil)
	 printf("L L\n");// no node
	 if(a->left==nil)
		printf("L ");
	else{
		printf("%d ",a->left->var);
		if(a->left->color==0)
		printf("B ");
		else	
		printf("R ");	
	}if(a->right==nil)
		printf("L\n");
	else{
		printf("%d ",a->right->var);
		if(a->right->color==0)
		printf("B \n");
		else	
		printf("R \n");
	}
}
struct node * uncle(struct node * a)
{
	if(a==NULL)
		return NULL;
	else if(a->parent==NULL)
		return NULL;
	else if(a->parent->parent==NULL)
		return NULL;// no grandparent implies no uncle
	else
	{
     a=a->parent;		
	 if(a==(a->parent->right))
	 {
		 if(a->parent->left==NULL)// no uncle
			return NULL;
		else
			return a->parent->left;
	}
	else
	{
		if(a->parent->right==NULL)// no uncle
			return NULL;
		else
			return a->parent->right;
	}
	
}}
void lrot(struct node * x,struct node **root)
{
	struct node *b,*y,*p; 
	if(x==NULL)
		return;
	if(x->right==NULL)
	return;
	y=x->right;
	b=y->left;
	p=x->parent;
	y->parent = p;
	x->parent = y;
	y->left = x;
	x->right=b;
	if(b!=nil)
	b->parent=x;
	if(p!=NULL)
	{
		if(x==p->right)
			p->right=y;
		else
			p->left=y;
			
	}
	if(x==*root)// shifting root
		*root=y;
}
void rrot(struct node * x,struct node **root)
{
	struct node *b,*y,*p; 
	if(x==NULL)
		return;
	if(x->left==NULL)
	return;
	y=x->left;
	b=y->right;
	p=x->parent;
	if(y!=nil)
	y->parent = p;
	x->parent = y;
	y->right = x;
	x->left=b;
	if(b!=nil)
	b->parent=x;
	if(p!=NULL)
	{
		if(x==p->right)
			p->right=y;
		else
			p->left=y;
			
	}
	
	if(x==*root)// shifting root
		*root=y;
}
	
void splice( struct node *b,struct node **root )//removal of a node with less than 2 children
{
	struct node *p,*s;
	if(b==*root)
	{
		if(b->left==nil&&b->right==nil)
			deltree(root);
		else if(b->left==nil)
		{
			(*root)=b->right;
			(*root)->color=0;
		}
		else
		{
			(*root)=b->left;
			(*root)->color=0;
		}
		free(b);
		return;
	}
	if(b->color==1)
	{
		p=b->parent;
		if(b==p->right)// node to be deleted is a right child
			{
				if((b->left==nil)&&(b->right==nil))// node has no children
					p->right=nil;
				else{
				if(b->right==nil)// node has a left child
				p->right=b->left;
				else// node has a right child
				p->right=b->right;
				p->right->parent=p;
				}
			}
		else// node to be deleted is a left child
		{
			if((b->left==nil)&&(b->right==nil))// node has no children
					p->left=nil;
			else{	
			if(b->right==nil)// node has a left child
				p->left=b->left;
				else// node has a right child
				p->left=b->right;
				p->left->parent=p;
			}
		}
	}
	
	
	else
	{
		p=b->parent;
		if(b->left==nil&&b->right==nil)
		{
			if(b==p->left)
			{
				p->left=nil;
				s=p->right;
				if(s->color==1)
				{
					s->color=0;
					p->color=1;
					lrot(p,root);
					s=p->right;
					if(s->left->color==0 && s->right->color==0)
					{
						s->color=1;
						blacken(p,root);	
					}
					else if(s->left->color==1&&s->right->color==0)
					{
						s->left->color=0;
						s->color=1;
						rrot(s,root);
						s=p->right;
						s->right->color=0;
						s->color=p->color;
						p->color=0;
						lrot(p,root);
						blacken(*root,root);
				
					}
					else{
						s->right->color=0;
						s->color=p->color;
						p->color=0;
						lrot(p,root);
						blacken(*root,root);
				
					}
				}
				else if(s->left->color==0 && s->right->color==0)
				{
					s->color=1;
					blacken(p,root);	
				}
				else if(s->left->color==1&&s->right->color==0)
				{
					s->left->color=0;
					s->color=1;
					rrot(s,root);
					s=p->right;
					s->right->color=0;
					s->color=p->color;
					p->color=0;
					lrot(p,root);
					blacken(*root,root);
				
				}
				else{
					s->right->color=0;
					s->color=p->color;
					p->color=0;
					lrot(p,root);
					blacken(*root,root);
				
				}
			}
			else
			{
				p->right=nil;
				s=p->left;
				if(s->color==1)
				{
					s->color=0;
					p->color=1;
					rrot(p,root);
					s=p->left;
					if(s->right->color==0 && s->left->color==0)
					{
						s->color=1;
						blacken(p,root);	
					}
					else if(s->left->color==0&&s->right->color==1)
					{
						s->right->color=0;
						s->color=1;
						lrot(s,root);
						s=p->left;
						s->left->color=0;
						s->color=p->color;
						p->color=0;
						rrot(p,root);
						blacken(*root,root);
				
					}
					else{
						
						s->left->color=0;
						s->color=p->color;
						p->color=0;
						rrot(p,root);
						blacken(*root,root);
				
					}
				}
				else if(s->left->color==0 && s->right->color==0)
				{
					s->color=1;
					blacken(p,root);	
				}
				else if(s->left->color==0&&s->right->color==1)
				{
					s->right->color=0;
					s->color=1;
					lrot(s,root);
					s=p->left;
					s->left->color=0;
					s->color=p->color;
					p->color=0;
					rrot(p,root);
					blacken(*root,root);
				
				}
				else{
					s->left->color=0;
					s->color=p->color;
					p->color=0;
					rrot(p,root);
					blacken(*root,root);
			
				}
			}
		}
			
		
		else
		{
			if(b==p->left)
			{
				if(b->left==nil)
					p->left=b->right;
				else
					p->left=b->left;
				p->left->parent=p;
				blacken(p->left,root);
			}
			else
			{
				if(b->left==nil)
					p->right=b->right;
				else
					p->right=b->left;
				p->right->parent=p;
				blacken(p->right,root);
			}
		}
		
	

	}
	
	free(b);
		b=NULL;
}
void blacken(struct node * a,struct node **root)
{
	struct node *s,*p;
	if(a->parent==NULL)
	{
		a->color=0;
		return ;
	}
	p=a->parent;
	if(a->color==1)
	{
	a->color=0;
	return;
	}
	if(a==p->left)
	{
		s=p->right;
		if(s->color==1)
		{
			p->color=1;
			s->color=0;
			lrot(p,root);
			blacken(a,root);
		}
		if(s->color==0 && s->left->color==0 && s->right->color==0)
		{
			s->color=1;
			blacken(p,root);
		}
		else if (s->right->color==1)
		{
			s->right->color=0;
			s->color=p->color;
			p->color=0;
			lrot(p,root);
			blacken(*root,root);
		}
		else
		{
			s->color=1;
			s->left->color=0;
			rrot(s,root);
			blacken(a,root);
		}
	}
	else
	{
		s=p->left;
		if(s->color==1)
		{
			p->color=1;
			s->color=0;
			rrot(p,root);
			blacken(a,root);
		}
		if(s->color==0 && s->left->color==0 && s->right->color==0)
		{
			s->color=1;
			blacken(p,root);
		}
		else if (s->left->color==1)
		{
			s->left->color=0;
			s->color=p->color;
			p->color=0;
			rrot(p,root);
			blacken(*root,root);
		}
		else
		{
			s->color=1;
			s->right->color=0;
			lrot(s,root);
			blacken(a,root);
		}
	}
}
void delnode(struct node **root, struct node *a)
{
	struct node *s;int tmp;
	
	if(a->right==nil || a->left==nil)
	{
		splice(a,root);// root must be changed
	}
	else// two children
	{
	s=succ(a->var,*root);
	tmp=s->var;
	s->var=a->var;
	a->var=tmp;// node value is replaced with successor node's value 
	splice(s,root);// previous successor node (which currently contains the former value of the node to be deleted) is deleted
	}
	
	
}
	