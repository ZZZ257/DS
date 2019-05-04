#include<stdio.h>
#include<stdlib.h>
struct node 
{
	int *b;
	int *p;
	char color;
	int n;
	struct node * adj;
};

struct queue
{
	
	struct node * a;
	struct queue * next;
	
};
void findpath(int u, int v, struct node **x,int N,int key);
int check(struct node *a,int j);
void init(struct node ** a, int N);	
void insert(struct node * a,int m);
void delete(struct node *x);
void deletegraph(struct node **a,int N);
void dequeue( struct queue **q);
void bfs(struct node **x,int m,int N);	
void enqueue( struct queue **q, struct node *b);

void main()
{
	struct node **a=NULL,**b,*p;
	int flag,flag1=0,x=0,y=0,N=0;
	char c;
	
	while((c=fgetc(stdin))!=EOF)
	{
		if(c=='P')
		{
			fgetc(stdin);
			flag=4;
			
		}
		else if(c=='N')
		{
			deletegraph(a,N);
			N=0;
			fgetc(stdin);
			flag=0;
			
		}
		else if(c=='?')
		{
			flag=2;
			fgetc(stdin);
		}
		else if(c=='E')
		{
			fgetc(stdin);
			flag=1;
			
		}
		else if(c==' ')
		{
			if(flag1==1)
			{
				
				{
			
			
				p=a[x-1];
				insert(p,y);
				
				}
				y=0;
			}
			
			flag1=1;
		}
		else if (c=='B')
		{
			flag=3;
			fgetc(stdin);
		}
		else if(c=='\n'){
			switch(flag)
			{
				case 0:
				a=(struct node**)malloc(x*sizeof(struct node*));
				init(a,x);
				N=x;
				break;
				case 1:
				if(flag1==1)
				p=a[x-1];
				insert(p,y);
				break;
				case 2:
				printf("%d\n",check(a[x-1],y));
				break;
				case 3:
				bfs(a,x,N);
				for(int i=0;(a[0]->b[i]>0)&&(i<N);i++)
					printf("%d ",a[0]->b[i]);
					printf("\n");
					
				break;
				case 4:
					findpath(x,y,a,N,0);
			}
			x=0;y=0;flag1=0;
			}
			
		
		
		
		else
		{
			if(flag1==0){
				
			x=x*10+(c-48);
			
			}
			else
			y=y*10+(c-48);
		
		}
		
	}
	
	
	
	
} 
void findpath(int u, int v, struct node **x,int N,int key)
{
	int  r=v,k=0,i=0,*path=(int *)malloc(N*sizeof(int));
	if((x[0]->p[u-1]==-1)||(x[0]->p[v-1]==-1))
	{
		bfs(x,u,N);		
	}// not present in bfs
	path[0]=v;
	while(x[0]->p[r-1]>0)
	{
		i++;
		r=x[0]->p[r-1];
		path[i]=r;
		if(r==u)
			k=1;
	}
	if(k==0)
	{
		i=0;
		r=u;
		path[0]=u;
		while(x[0]->p[r-1]>0)
	{
		i++;
		r=x[0]->p[r-1];
		path[i]=r;
		
		if(r==v)
			k=2;
	}}
	
	if(k==0){
		if(key==1)
		printf("-1\n");
		else
		{
			bfs(x,u,N);
			findpath(u,v,x,N,1);//key is used so that this function is not used more than twice by recursion
			
		}
	}
	if(k==1)
	{
		
		for(i=0;path[i]!=u;i++);
		for(;i>=0;i--)
		printf("%d ",path[i]);
		printf("\n");
	}
	if(k==2)
	{
		for(i=0;path[i]!=v;i++)
			printf("%d ",path[i]);
		printf("%d\n",path[i]);
	}
	free(path);
}

void bfs(struct node **x,int m,int N)
{
	for(int j=0;j<N;j++)
	{
		(x[0])->b[j]=-1;
		(x[0])->p[j]=-1;
		}// initialisation
	struct node * y,*z;
	struct queue *q=NULL;
	int i=0,j=m;
	y=x[m-1];
	x[0]->p[m-1]=0;
	enqueue(&q,y);
	while(q!=NULL)
	{
		
		z=x[(y->n)-1];
		if(z->color==0)
		{
			
			x[0]->p[z->n-1]=j;// parent of z->n is j, which is value of node whose adjacency list is in consideration afterprevious dequeueing 
			
			enqueue(&q,z);
		}
		
		if(y->adj==NULL)
		{	
		x[0]->b[i]=q->a->n;
		i++;
		dequeue(&q);
		if(q!=NULL)
		y=x[(q->a->n)-1];
		j=y->n;
		}
		else
		{
		y=y->adj;
		}
	}

	
	for(int i=0;i<N;i++)
					x[i]->color=0;// all are reset to be made to do breadth first search again
	
}
void enqueue( struct queue **q, struct node *b)
{// insert node into queue
	
	struct queue *q2=*q,*q1=(struct queue*)malloc(sizeof(struct queue));
	q1->a=b;
	q1->next=NULL;
	b->color=1;
	if((*q)!=NULL)
	{
		
	while((q2->next)!=NULL)
	{
		q2=q2->next;
		
	}
	q2->next=q1;
	
	}
	else
		(*q)=q1;


}
void dequeue( struct queue **q)
{
	struct queue *q1=*q;
	q1->a->color=2;
		
	(*q)=(*q)->next;
	free(q1);
	


}
void init(struct node ** a, int N)
{
	int i;
	
	
	for(i=0;i<N;i++)
	{
		
		a[i]=(struct node*)malloc(sizeof(struct node));
		(a[i])->n=i+1;
		(a[i])->adj=NULL;
		(a[i])->color=0;
		
	}
	(a[0])->b=(int *)malloc(N*sizeof(int));//to hold result of breadth first search in order of dequeueing
	(a[0])->p=(int *)malloc(N*sizeof(int));// to hold parent of dequeued elements
}
void insert(struct node *ptr,int m)// to create adjacency list 
{
	
	struct node *ptr1=(struct node*)malloc(sizeof(struct node));
	
	while((ptr->adj)!=NULL)		
	ptr=ptr->adj;
	ptr1->n=m;
	ptr1->adj=NULL;
	ptr->adj=ptr1;
}
void delete(struct node *x)
{
	struct node *ptr;
	while(x!=NULL)
	{
		ptr=x;
		x=x->adj;
		free(ptr);
	}
	
	
}
void deletegraph(struct node **a,int N)
{
	
	int i;
	for(i=0;i<N;i++)
	{
		delete(a[i]);
		a[i]=NULL;
	
	}
	
	if(a!=NULL)
	free(a);

	}
	




int check(struct node *a,int j)

{
	
	struct node* p=a;

	int k=0;
	while(p!=NULL){
		
		if(p->n==j)// looking for j in adjacency list of a
		k++;
		p=p->adj;
}
	return k; 
}







