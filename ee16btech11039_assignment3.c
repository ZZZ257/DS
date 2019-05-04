
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
struct node * succ(struct number *, struct node *);
void delnode(struct node **, struct node **);
void deltree(struct node **);
void display(struct number *);
struct node * search(struct node *,struct number *, int);
void traverse(struct node *);
void ins(struct number**,int );
void insert(struct node**,struct number* );
int cmp(struct number*, struct number*);
void del(struct number**);
void splice( struct node **);
int main()
{
	struct number *a=NULL;int flag0=0,flag1=0;//flag0 for showing insert , search or traversal, flag1 to take care of stray zeros
		struct node *root=NULL;
		
		struct node *s;
	char c;
	while((c=fgetc(stdin))!=EOF)
	{	
		if(c=='+')//same as insertion but tree is not deleted
		    flag0=0;
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
			
			
			if((flag1==0)&&(flag0==2))
				ins(&a,'0');//insert zero to list if entire string was a set of zeroes without a non zero number(insert removes all zeros before a nonzero number)
			
		
			if(flag0==2)// a number is inserted after an 'N' or '+'
			{
				insert(&root,a);
	            a=NULL;     
			}
			if(flag0==0)//space after an N or a +, flag0=2 indicates that preceding string was a number
				flag0=2;
			
			flag1=0;// new number
		}
	else if(c=='\n')
	{	
		
		switch(flag0)
		{
			case -1://traversal	
			traverse(root);
				printf("\n");
				break;
			case 4://successor
				s=succ(a,root);
				if(s!=NULL)
				display(s->var);
				else
				printf("-1");
				printf("\n");
				del(&a);
				break;
				
			case 3://deletion
			    s=search(root,a,0);
				if(s!=NULL);
				delnode(&root,&s);
				del(&a);
				break;
			case 1://search
				if(flag1==0)
				ins(&a,'0');	
				search(root,a,1);
				del(&a);
				break;
			
			case 2://last number
				if(flag1==0)
				ins(&a,'0');
				insert(&root,a);
				a=NULL;
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
		ptr1->var=n;
		ptr1->parent=ptr2;
		if(k==-1)
			ptr2->left=ptr1;
		else
			ptr2->right=ptr1;
		ptr1->left=NULL;
		ptr1->right=NULL;
	}
}
struct node * search(struct node *x,struct number *n, int p)// p=0 indicates that address of node that contains number n must be returned p=1 indicates that path must printed 
{
	int k=0;
	struct number * b=NULL;
	while (x!=NULL)
	{
		if(cmp(x->var,n)==0)// equal
		{
			k=1;
			break;
		}
		else if (cmp(x->var,n)==1)// n < x->var
		{
			ins(&b,'0');
			x=x->left;
		}
		else// n > x->var
		{ 
			x=x->right;
			ins(&b,'1');
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
struct node * succ(struct number *a, struct node *root)
{
	if(root==NULL)
		return NULL;
	struct node *y=NULL,*x = search(root,a,0);int flag =0;
	
	if(x==NULL)// if a is not present in the BST
	{	
		
		
		insert(&root,a);
		x = search(root,a,0);
		flag=1;// for deletion of inserted node, is a was inserted, it would be a leaf node
		y=x;	
	}
	
	if(x->right==NULL)
	{
		if(flag==1)
		{
			x=x->parent;
			if(y==x->right)
				x->right=NULL;
			else
			{
				x->left=NULL;
				return x;// immediate parent after insertion is successor
			}
			y->parent=NULL;
			free(y);// y is an independent node
			
				
				
		}
		
		while((x->parent)!=NULL)
		{
			if(cmp(x->var,x->parent->var)==-1)// when a parent of a node is greater than itself , the parent is greater than every element in the subtree 
				return (x->parent);	
			
			x=x->parent;
		}
		return NULL;
	}
	else// node has a right child
	{ 
		x=x->right;
		while((x->left)!=NULL)
		x=x->left;
		return x;
	}
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
	struct node *s;struct number * tmp;
	
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










