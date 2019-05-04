
#include<stdio.h>
#include<stdlib.h>

struct heap
{
	int n;
	int parent;
	int distance;

};
void heapify(struct heap *q,int i )
{
	
	
	struct heap temp;
	while(i>0)
	{
		
		if(((q[i].distance<q[(i-1)/2].distance)||(q[(i-1)/2].distance==-1))&&(q[i].distance>-1))
		{
			temp.n=q[i].n;
			temp.distance=q[i].distance;
			temp.parent=q[i].parent;
			q[i].n=q[(i-1)/2].n;
			q[i].distance=q[(i-1)/2].distance;
			q[i].parent=q[(i-1)/2].parent;
			q[(i-1)/2].n=temp.n;
			q[(i-1)/2].distance=temp.distance;
			q[(i-1)/2].parent=temp.parent;
			
			
		}
		
		
		
		//else
			//break;
		i=(i-1)/2;
	}
}

void insertH(struct heap *q,int x,int y, int z)
{
	int i;
	for( i=0;(q[i].n!=x)&&((q[i].n>-1));i++);
	if(q[i].n==x)
	if((q[i].distance==-1)||(q[i].distance>z))
	{
	q[i].parent=y;
	q[i].distance=z;
	}heapify(q,i);
}


void deletemin(struct heap *q)
{
	int i;
	struct heap temp;
	for(i=0;(i<6)&&(q[i+1].parent>=0);i++);
	
	q[0].parent=q[i].parent;
	q[0].n=q[i].n;
	q[0].distance=q[i].distance;
	q[i].parent=-1;
	q[i].distance=-1;
	q[i].n=-1;
	i=1;
	while(((q[i-1].distance>q[2*i].distance)||(q[i-1].distance>q[2*i-1].distance))&&(q[2*i].distance>=0))
	{
		if(q[2*i].distance>q[2*i-1].distance)
		{
			temp.n=q[i-1].n;
			temp.parent=q[i-1].parent;
			temp.distance=q[i-1].distance;
			q[i-1].n=q[2*i-1].n;
			q[i-1].parent=q[2*i-1].parent;
			q[i-1].distance=q[2*i-1].distance;
			q[2*i-1].n=temp.n;
			q[2*i-1].parent=temp.parent;
			q[2*i-1].distance=temp.distance;
			i=2*i-1;
		}
		else{temp.n=q[i-1].n;
			temp.parent=q[i-1].parent;
			temp.distance=q[i-1].distance;
			q[i-1].n=q[2*i].n;
			q[i-1].parent=q[2*i].parent;
			q[i-1].distance=q[2*i].distance;
			q[2*i].n=temp.n;
			q[2*i].parent=temp.parent;
			q[2*i].distance=temp.distance;
			i=2*i;
			}
			
	}
	if((q[2*i-1].distance>=0)&&(q[i-1].distance>q[2*i-1].distance))
	{
		
			temp.n=q[i-1].n;
			temp.parent=q[i-1].parent;
			temp.distance=q[i-1].distance;
			q[i-1].n=q[2*i-1].n;
			q[i-1].parent=q[2*i-1].parent;
			q[i-1].distance=q[2*i-1].distance;
			q[2*i-1].n=temp.n;
			q[2*i-1].parent=temp.parent;
			q[2*i-1].distance=temp.distance;
			
		
	}

}

void main()
{
	struct heap *q=(struct heap*)malloc(7*sizeof(struct heap));
	for(int j=0;j<7;j++)
	{
		q[j].distance=-1;
		q[j].parent=-1;
		q[j].n=j+1;
		}
	//insertH(q,1,0,7);
	//insertH(q,2,0,6);
//insertH(q,3,0,5);
insertH(q,4,0,4);
insertH(q,5,0,3);
//insertH(q,6,0,2);
//insertH(q,7,0,1);	

for(int i=0;i<7;i++)
printf("%d %d ",q[i].n ,q[i].distance);	
for(int i=0;i<7;i++)
{
printf("\n");
	deletemin(q);
	//	for(int j=0;j<7;j++)
	//printf("%d %d ",q[j].n ,q[j].distance);
	//insertH(q,7-i,0,1);
	//printf("\n");
	for(int j=0;j<7;j++)
printf("%d %d ",q[j].n ,q[j].distance);	

	
}
insertH(q,7,0,1);
printf("\n\n%d %d ",q[0].n ,q[0].distance);
}