
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
	struct node * left;
	struct node * parent;
	struct node * right;
};
struct stack//for better insertion into tree given preorder traversal
{
	struct node * x;
	struct stack * next;
};
void preorder(struct node **,struct stack **, int );
void push(struct stack **, struct node * );
void pop(struct stack **);	
void lrot();
void rrot();
struct node * uncle(struct node * a);
void children(struct node * a);
void ins(struct list **,int );
void del(struct list **);
void display(struct list *);
struct node * succ(int, struct node *);
void delnode(struct node **, struct node **);
void deltree(struct node **);
struct node * search(struct node *,int, int);
void traverse(struct node *);
struct node * insert(struct node**,int );
void splice( struct node **);
int main()
{
	int a=0;int flag0=0;//flag0 for showing insert , search or traversal,adding element, removing element, successor, insert by preorder, rotate, find uncle, find children
		struct node *root=NULL;
		struct stack *head=NULL,*ptr;
		struct node *s;
	char c;
	while((c=fgetc(stdin))!=EOF)
	{	
		if(c=='B')// insert in order
		{
			while(head!=NULL){
				ptr=head;
				head=head->next;
				free(ptr);
			}
			deltree(&root);
			flag0=10;
		}
		else if(c=='+')//same as insertion but tree is not deleted
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
			
		if(flag0==9)
			{
				preorder(&root,&head,a);
				a=0;
			}
			

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
				delnode(&root,&s);
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
			case 9:
				
				preorder(&root,&head,a);	
				
			push(&head,s);
				
		}
		
		a=0;
		
	}
  else
	{
		
		a=(a*10)+c-48;
	
	}	
    }
deltree(&root);
free(nil);
return 0;



}
void traverse(struct node *ptr)//preorder traversal by recursion
{
	if(ptr!=NULL)
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
	(*root)->left=NULL;
	(*root)->right=NULL;
	return (*root);
	
	}
	
	else
	{//insertion to bst
		while (ptr1!=NULL)
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
		ptr1->left=NULL;
		ptr1->right=NULL;
		return ptr1;
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
	if((*a)!=NULL)
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
		if((y->right!=NULL))
	{ 	
		x=y;
		x=x->right;
		while((x->left)!=NULL)
		x=x->left;
		
	}}
	return x;
}
void splice( struct node **a )//removal of a node with less than 2 children
{
	struct node *b=*a;
	
	
	 if((*a)->parent==NULL)// in case of deletion of root, root has to be changed and previous root must be deallocated
	{
		if((*a)->right!=NULL)
		{
			*a=(*a)->right;
			(*a)->parent=NULL;
			free(b);
		}
		else if((*a)->left!=NULL)
		{
			*a=(*a)->left;
			(*a)->parent=NULL;
			free(b);
		}
		else// root with no children
		{
			deltree(a);
		}
	}
	else{
		*a=b->parent;
	 if(b==((*a)->right))// node to be deleted is a right child
			{
				if((b->left==NULL)&&(b->right==NULL))// node has no children
					(*a)->right=NULL;
				else{
				if(b->right==NULL)// node has a left child
				(*a)->right=b->left;
				else// node has a right child
				(*a)->right=b->right;
				(*a)->right->parent=*a;
				}
			}
		else// node to be deleted is a left child
		{
			if((b->left==NULL)&&(b->right==NULL))// node has no children
					(*a)->left=NULL;
			else{	
			if(b->right==NULL)// node has a left child
				(*a)->left=b->left;
				else// node has a right child
				(*a)->left=b->right;
				(*a)->left->parent=*a;
			}
		}	
		free(b);
		b=NULL;
	}
}
void delnode(struct node **root, struct node **a)
{
	struct node *s;int tmp;
	
	if(((*a)->right==NULL)||((*a)->left==NULL))
	{
		if(*a==*root)
		splice(root);// root must be changed
		else
		splice(a);
	}
	else// two children
	{
	s=succ((*a)->var,*root);
	tmp=s->var;
	s->var=(*a)->var;
	(*a)->var=tmp;// node value is replaced with successor node's value 
	splice(&s);// previous successor node (which currently contains the former value of the node to be deleted) is deleted
	}
	
	
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
	if(a==NULL)
	 printf("Nil Nil\n");// no node
	else{ 
		if(a->left==NULL)
		printf("Nil ");
	else
		printf("%d ",a->left->var);
	if(a->right==NULL)
		printf("Nil\n");
	else
		printf("%d\n",a->right->var);
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
	if(b!=NULL)
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
	y->parent = p;
	x->parent = y;
	y->right = x;
	x->left=b;
	if(b!=NULL)
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
	
void push(struct stack **h, struct node * y)
{
struct stack *ptr=(struct stack*)malloc(sizeof(struct stack));
ptr->x=y;
ptr->next=*h;
*h=ptr;
}

void pop(struct stack **h)
{
struct stack *ptr=*h;
*h=(*h)->next;
free(ptr);
}
void preorder(struct node **root,struct stack ** head, int a)
{
				struct node *s;
				if(*head==NULL)	
				s=insert(root,a);
				
				else{
					
					while(((*head)->next)!=NULL){
						
						
							if(a>((((*head)->next)->x)->var))
							pop(head);// if something has something to its right or its ancestor has a child to its right, it cannot have anymore children in the preorder traversal
							else break;
						}
					s=insert(&((*head)->x),a);
					if(a>(((*head)->x)->var))
					pop(head);	// if right is filled, the given node cannot have anymore children
				}
			push(head,s);// the stack contains only those elements which can have children and whose children can occur in the unchecked parts of the in prder traversal
				a=0;
	
}
	