#include<stdio.h>
#include<stdlib.h>
struct node 
{
	
	char color;
	int n;
	struct node * adj;
};

struct queue
{
	int d;
	struct node * a;
	struct queue * next;
	
};
int check(struct node *a,int j);
void init(struct node ** a, int N,int **b,int **p);	
void insert(struct node * a,int m);
void delete(struct node *x);
void deletegraph(struct node **a,int N,int *b,int *p);
void dequeue( struct queue **q);
void bfs(struct node **x,int m,int *b,int * p,int N);	
void enqueue( struct queue **q, struct node *b);
void path(int u, int v, struct node **x, int *b,int *p,int N);
void main()
{
	struct node **a=NULL,**b,*p;
	struct queue *q;
	int flag,flag1=0,x=0,y=0,N=0,*brfs=NULL,*brfsp=NULL;
	char c,ch;
	
	while((c=fgetc(stdin))!=EOF)
	{
		if(c=='P')
		{
			fgetc(stdin);
			flag=4;
		}
		else if(c=='N')
		{
			if(brfs!=NULL)
				free(brfs);
			if(brfsp!=NULL)
				free(brfsp);
			deletegraph(a,N,brfs,brfsp);
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
				init(a,x,&brfs,&brfsp);
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
				bfs(a,x,brfs,brfsp,N);
				for(int i=0;brfs[i]>0&&(i<N);i++)
					printf("%d ",brfs[i]);
				printf("\n");
				for(int i=0;i<N;i++)
					a[i]->color=0;
					break;
				case 4:
					path(x,y,a,brfs,brfsp,N);
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
		ch=c;
	}
	
	
	
	
}
void path(int u, int v, struct node **x, int *b,int *p,int N)
{
	int  r=u,k=0,i=0,*path=(int *)malloc(N*sizeof(int));
	if((p[u-1]==-1)||(p[v-1]==-1))
		bfs(x,u,b,p,N);
	path[0]=u;
	while(p[r-1]>0)
	{
		
		r=p[r-1];
		if(r==v){
			k=1;
			
	}
	
	i++;
	path[i]=r;
	}
	if(k==0)
	{
		i=0;
		r=v;
		path[0]=v;
		while(p[r-1]>0)
	{
		
		r=p[r-1];
		if(r==v){
			k=2;
		path[i]=r;
	i++;	
	}
	}
	if(k==0)
		printf("-1\n");
	if(k==1)
	{
		for(i=0;path[i]!=v;i++)
			printf("%d",path[i]);
		printf("%d\n",path[i]);
	}
	if(k==2)
	{
		for(i=0;path[i]!=u;i++)
			printf("%d",path[i]);
		printf("%d\n",path[i]);
	}
	
}}
void bfs(struct node **x,int m,int *b,int * p,int N)
{
	struct node * y,*z;
	struct queue *q=NULL;
	int i=0,j=m;
	
	for(i=0;i<N;i++)
	{
		b[i]=-1;
		p[i]=-1;
	}
	
	y=x[m-1];
	enqueue(&q,y);
	p[m-1]=0;
	while(q!=NULL)
	{
		j=(y->n)-1;
		z=x[j];
		if(z->color==0)
		{
			enqueue(&q,z);
		}
		
		if(y->adj==NULL)
		{	
		b[i]=q->a->n;
		i++;
		dequeue(&q);
		if(q!=NULL)
		y=x[(q->a->n)-1];
		
		}
		else
		{
			
		y=y->adj;
		}
		
	}

	
	
	
}
void enqueue( struct queue **q, struct node *b)
{
	
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
void init(struct node ** a, int N,int ** b,int ** p)
{
	int i;
	
	*p=(int *)malloc(N*sizeof(int));
	*b=(int *)malloc(N*sizeof(int));
	for(i=0;i<N;i++)
	{
		
		a[i]=(struct node*)malloc(sizeof(struct node));
		(a[i])->n=i+1;
		(a[i])->adj=NULL;
		(a[i])->color=0;
		
	}
	
}
void insert(struct node *ptr,int m)
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
void deletegraph(struct node **a,int N,int *b,int *p)
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
	p=p->adj;
	while(p!=NULL){
		
		if(p->n==j)
		k++;
		p=p->adj;
}
	return k; 
}







