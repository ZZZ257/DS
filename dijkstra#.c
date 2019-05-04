#include<stdio.h>
#include<stdlib.h>
struct node 
{
	int *b;
	int *p;
	int *dis;
	char color;
	int n;
	int d;
	struct node * adj;
};

struct heap
{
	int n;
	int parent;
	int distance;

};
void swap(struct heap *x,struct heap * y);
void deletemin(struct heap *q,int N);
void insertH(struct heap *q,int x,int y, int z,int N);
void heapify(struct heap *q,int i );
void findpath(int u, int v, struct node **x,int N,int key);
int check(struct node *a,int j);
void init(struct node ** a, int N);	
void insert(struct node * a,int m,int k);
void delete(struct node *x);
void deletegraph(struct node **a,int N);
//void dequeue( struct queue **q);
void dijkstra(struct node **x,int m,int N);	
//void enqueue( struct queue **q, struct node *b);

void main()
{
	struct node **a=NULL,**b,*p;
	int flag,flag1=0,x=0,y=0,z=0,N=0;
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
			if(flag==1){
			if(flag1==1)
				flag1=2;
			else if(flag1==2)
			{
				{			
				p=a[x-1];
				insert(p,y,z);
				
				}
				y=0;
				z=0;
				flag1=1;
			}
			
			}
			if(flag1==0)
				flag1=1;
		}
		else if (c=='D')
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
				p=a[x-1];
				insert(p,y,z);
				break;
				case 2:
				printf("%d\n",check(a[x-1],y));
				break;
				case 3:
				dijkstra(a,x,N);
				for(int i=0;(a[0]->b[i]>0)&&(i<N);i++)
					printf("%d %d\n",a[0]->b[i],a[0]->dis[a[0]->b[i]-1]);
					for(int i=0;(i<N);i++)
					if(a[0]->p[i]==-1)
					printf("%d %d\n",i+1,a[0]->dis[i]);
					
				break;
				case 4:
					findpath(x,y,a,N,0);
			}
			x=0;y=0;z=0;flag1=0;
			}
			
		
		
		
		else
		{
			if(flag1==0){
				
			x=x*10+(c-48);
			
			}
			else if(flag1==1)
			y=y*10+(c-48);
			else
			z=z*10+(c-48);	
		}
		
	}
	
	
	
	
} 
void findpath(int u, int v, struct node **x,int N,int key)
{
	int  d,r=v,k=0,i=0,*path=(int *)malloc(N*sizeof(int));
	if((x[0]->p[u-1]==-1)&&(x[0]->p[v-1]==-1))
	{
		dijkstra(x,u,N);		
	}// not present in dijkstra
	if((x[0]->p[u-1]!=-1)&&(x[0]->p[v-1]==-1))
	{
		printf("-1\n");
		return;
	}
	path[0]=v;
	while(x[0]->p[r-1]>0)
	{
		i++;
		r=x[0]->p[r-1];
		path[i]=r;
		if(r==u)
			k=1;
	}
	if(v==u)
			k=1;
	
	if(k==0){
		if(key==1)
		printf("-1\n");
		else
		{
			dijkstra(x,u,N);
			findpath(u,v,x,N,1);//key is used so that this function is not used more than twice by recursion
			
		}
	}
	if(k==1)
	{
		d=x[0]->dis[v-1]-x[0]->dis[u-1];
		printf("%d ",d);
		for(i=0;path[i]!=u;i++);
		for(;i>=0;i--)
		printf("%d ",path[i]);
		printf("\n");
	}
	free(path);
}

void dijkstra(struct node **x,int m,int N)
{
	struct heap *q=(struct heap*)malloc(N*sizeof(struct heap)),q1;
	for(int j=0;j<N;j++)
	{
		(x[0])->b[j]=-1;
		(x[0])->p[j]=-1;
		(x[0])->dis[j]=-1;
		
	}// initialisation
	struct node * y,*z;
	
	for(int j=0;j<N;j++)
	{
		q[j].distance=-1;
		q[j].parent=-1;
		q[j].n=j+1;
		}
		int i=0,j=m;
	insertH(q,m,0,0,N);
	
	while(q[0].distance!=-1)
	{//extracting minimum-beg
		q1.distance=q[0].distance;
		q1.parent=q[0].parent;
		q1.n=q[0].n;
		deletemin(q,N);
		j=q1.n;
		x[0]->p[j-1]=q1.parent;
		x[0]->dis[j-1]=q1.distance;
		x[0]->b[i]=j;
		i++;
		//extracting minimum-end
		//insertion-beg
		y=x[j-1];
		while(y->adj!=NULL)
		{
		y=y->adj;
		if((x[0]->dis[y->n-1]==-1)||((x[0]->dis[j-1]+y->d)<x[0]->dis[y->n-1]))
		{
			x[0]->dis[y->n-1]=x[0]->dis[j-1]+y->d;
			insertH(q,y->n,j,x[0]->dis[y->n-1],N);	
			
		}
		//insertion-end
		}
		
	}
	
	
	
	}
void init(struct node ** a, int N)
{
	int i;
	
	
	for(i=0;i<N;i++)
	{
		
		a[i]=(struct node*)malloc(sizeof(struct node));
		(a[i])->n=i+1;
		(a[i])->d=0;
		(a[i])->adj=NULL;
		(a[i])->color=0;
		
	}
	(a[0])->dis=(int *)malloc(N*sizeof(int));//to hold distance of extracted elements
	(a[0])->b=(int *)malloc(N*sizeof(int));//to hold result of dijkstra's algorithm in order of extraction from priority queue
	(a[0])->p=(int *)malloc(N*sizeof(int));// to hold parent of extracted elements
	for(i=0;i<N;i++)
	{
		a[0]->p[i]=-1;
		}
}
void insert(struct node *ptr,int m,int k)// to create adjacency list 
{
	struct node *ptr1=(struct node*)malloc(sizeof(struct node));
	while((ptr->adj)!=NULL)		
	ptr=ptr->adj;
	ptr1->n=m;
	ptr1->d=k;
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
	

void deletemin(struct heap *q,int N)
{
	int i;
	struct heap temp;
	for(i=0;(i<N-1)&&(q[i+1].n>0);i++);
	q[0].parent=q[i].parent;
	q[0].n=q[i].n;
	q[0].distance=q[i].distance;
	q[i].parent=-1;
	q[i].distance=-1;
	q[i].n=-1;
	i=1;
	while(((q[i-1].distance>q[2*i].distance)||(q[i-1].distance>q[2*i-1].distance))&&(q[2*i].distance>=0)&&(q[2*i].distance>=0))
	{
		if(q[2*i].distance>q[2*i-1].distance)
		{
			swap(&q[i-1],&q[2*i-1]);
			i=2*i-1;
		}
		else{swap(&q[i-1],&q[2*i]);
		i=2*i;
			}
			
	}
	if((q[2*i-1].distance>=0)&&(q[i-1].distance>q[2*i-1].distance))
	{
		swap(&q[i-1],&q[2*i-1]);
			
		
	}//heap not full
	
}
void insertH(struct heap *q,int x,int y, int z,int N)
{
	int i;
	for( i=0;(q[i].n!=x);i++);
	if(q[i].n==x)
	if((q[i].distance==-1)||(q[i].distance>z))
	{
	q[i].parent=y;
	q[i].distance=z;
	}heapify(q,i);
	
}

void swap(struct heap *x,struct heap * y)
{
			struct heap temp;
			temp.n=x->n;
			temp.parent=x->parent;
			temp.distance=x->distance;
			x->n=y->n;
			x->parent=y->parent;
			x->distance=y->distance;
			y->n=temp.n;
			y->parent=temp.parent;
			y->distance=temp.distance;
	
	
	
}

void heapify(struct heap *q,int i )
{
	
	
	struct heap temp;
	//while(q[i-1].distance==-1)
	//{
		//swap(&q[i-1],&q[i]);
			//i--;
			
	//}// to manage heap property
	
	while(i>0)
	{
		
		if(((q[i].distance<q[(i-1)/2].distance)||(q[(i-1)/2].distance==-1))&&(q[i].distance>-1))	
		{
			swap(&q[i],&q[(i-1)/2]);
			
			
		}
		
		
		
		//else
			//break;
		i=(i-1)/2;
	}
}
	
	


int check(struct node *a,int j)

{
	
	struct node* p=a;

	int k=-1;
	p=p->adj;
	while(p!=NULL){
		
		if(p->n==j)// looking for j in adjacency list of a
		k=p->d;
		p=p->adj;
}
	return k; 
}







