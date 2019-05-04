#include<stdio.h>
#include<stdlib.h>
struct node 
{
	int n;
	int rank;
	struct node *parent;
};
void delete(struct node **a,int N);
void Union(int x,int y,struct node **a);
void init(int N, struct node **a);
struct node * rep(int x,struct node **a);
int check(int x,int y,struct node **a);
void main()
{
	struct node **a=NULL,**b,*p;
	int flag,flag1=0,x=0,y=0,N=0;
	char c;
	
	while((c=fgetc(stdin))!=EOF)
	{
		if(c=='R')
		{
			fgetc(stdin);
			flag=3;
			
		}
		else if(c=='N')
		{
			delete(a,N);
			N=0;
			fgetc(stdin);
			flag=0;
			
		}
		else if(c=='S')
		{
			flag=2;
			fgetc(stdin);
		}
		else if(c=='U')
		{
			fgetc(stdin);
			flag=1;
			
		}
		else if(c=='?')
		{
			fgetc(stdin);
			flag=4;
			
		}
		else if(c==' ')
			flag1=1;
		
		else if(c=='\n'){
			switch(flag)
			{
				case 0:
				N=x;
				a=(struct node**)(malloc(N*sizeof(struct node *)));
				init(N,a);
				break;
				case 1:
				Union(x,y,a);
				break;
				case 2:
				printf("%d\n",(rep(x,a)->n));
				break;
				case 3:
				printf("%d\n",a[x-1]->rank);
					
				break;
				case 4:
				if((x<=N)&&(y<=N))
					printf("%d\n",check(x,y,a));
				else
					printf("%d\n",-1);
				break;
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
int check(int x,int y,struct node **a)
{
	if(rep(x,a)==rep(y,a))
		return 1;
	else
		return 0;
	
}
struct node * rep(int x,struct node **a)
{
	struct node *p=a[x-1];
   while(p->parent!=NULL)
   {
	   p=p->parent;
	
   }return p;

}	
void init(int N, struct node **a)
{
	for(int i=0;i<N;i++)
	{
		a[i]=(struct node*)malloc(sizeof(struct node));
		a[i]->parent=NULL;
		a[i]->rank=1;
		a[i]->n=1+i;
		
	}
	
	
}
void Union(int x,int y,struct node **a)
{
	struct node *a1,*a2;
	a1=rep(x,a);
	a2=rep(y,a);
	if(a1->rank<a2->rank)
		a1->parent=a2;
	else
		a2->parent=a1;
	if(a1->rank==a2->rank)	
	(a1->rank)++;
}
void delete(struct node **a,int N)
{
	for(int i=0;i<N;i++)
		free(a[i]);
	
	free(a);
	
}