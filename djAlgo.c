#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int len=0;
int n=-1;
int * priority_queue=NULL;
int * distance=NULL;
int * pi=NULL;

typedef struct vertex{
    int v;
    int weight;
    struct vertex * next;
    int visited;
}vertex;

vertex * V=NULL;

void swap(int * arr,int i,int j)
{
	int temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
}

void Min_heapify( int * priority_queue, int prQ_indx, int n)
{
	int smallest=prQ_indx;
	int left=prQ_indx*2+1;
	int right=prQ_indx*2+2;
	if(left<n && distance[priority_queue[smallest]]>distance[priority_queue[left]])
	{
		smallest=left;
	}
	if(right<n && distance[priority_queue[smallest]]>distance[priority_queue[right]])
	{
		smallest=right;
	}
	if(smallest!=prQ_indx)
	{
		swap(priority_queue,smallest,prQ_indx);
		Min_heapify(priority_queue,smallest,n);
	}
}

void Build_priorityQ( int * priority_queue, int n)
{
	int i;
	for(i=n/2-1;i>=0;i--)
	{
		Min_heapify(priority_queue,i,n);
	}
}

void DijkstraAlgorithm(int s)
{
    while(len!=0)
    {
        // printf("HELLO!!\n");
        int u=priority_queue[0];
        vertex * head=V[u].next;
        vertex * temp=head;
        while(head!=NULL)
        {
            // printf("ROOT VERTEX %d ADJ VERTEX:%d\n",u,head->v);
            // printf("PARENT:");
            // display(pi,n);
            // printf("DISTANCE:");
            // display(distance,n);


            int w=head->weight;
            // printf("The weight is %d\n\n",w);
            if(V[head->v].visited==0)
            {
                V[head->v].visited=1;
                priority_queue[len++]=head->v;
            }
            if(distance[head->v]>distance[u]+w && head->v!=pi[u])
            {
                distance[head->v]=distance[u]+w;
                pi[head->v]=u;
            }
            head=head->next;
        }
        swap(priority_queue,0,--len);
        Build_priorityQ(priority_queue,len);
    }
}

void displayAdjList(vertex * V, int n)
{
	int i, j;
	vertex * head;
	printf("The Adjacency List is:\n");
	for(i=0; i<n; i++)
	{
		printf("V%d : ",i);
		head=V[i].next;
		while(head!=NULL)
		{
			printf("vertex:%d,weight:%d --> ",head->v,head->weight);
			head=head->next;
		}
		printf("NULL\n");
	}
}

vertex * insertBeg(vertex * head, int v, int w)
{
	vertex * p=(vertex *)malloc(sizeof(vertex));
	p->v=v;
	p->weight=w;
	p->next=head;
	head=p;
	return head;
}

vertex * createAdjList(vertex * V)
{
    int u, v, w, i;
	FILE * fp;
	fp=fopen("./edgeList1.txt", "r");
	if(fp==NULL)
	{
		printf("Error in opening file2!\n");
	}
	else
	{
		fscanf(fp,"%d\n", &n);
        V=(vertex *)malloc(sizeof(vertex)*n);
		for(i=0; i<n; i++)
		{
			V[i].v=i;
            V[i].weight=0;
            V[i].next=NULL;
            V[i].visited=0;
		}
		while(!feof(fp))
		{
			fscanf(fp,"%d %d %d\n", &u, &v, &w);
			V[u].next=insertBeg(V[u].next,v,w);
			V[v].next=insertBeg(V[v].next,u,w);			
		}
		fclose(fp);
	}
    return V;
}

void display(int * arr,int n)
{
    int i;
    // printf("The array is:\n");
    for(i=0;i<n;i++)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
}

void displayPath(int s)
{
    int i,node;
    for(i=0;i<n;i++)
    {
        node=pi[i];
        printf("%d<---",i);
        while(node!=-1)
        {
            printf("%d <--",node);
            node=pi[node];
        }
        //printf("%d",s);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int s,i;
    printf("Enter the source Vertex:");
    scanf("%d",&s);
	V=createAdjList(V);
    //printf("%d\n\n",n);
    displayAdjList(V,n);
    priority_queue=(int *)malloc(sizeof(int)*n);
    distance=(int *)malloc(sizeof(int)*n);
    pi=(int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++)
    {
        distance[i]=INT_MAX;
        pi[i]=INT_MAX;
    }
    len=0;
    priority_queue[len++]=s;
    distance[s]=0;
    pi[s]=-1;
    DijkstraAlgorithm(s);

    printf("The Parent Array is:\n");
    display(pi,n);
    printf("The Distance Array is:\n");
    display(distance,n);

    printf("The shortest paths from the source %d is:\n",s);
    displayPath(s);
	return 0;	
}

// edgeList1.txt

// 6
// 0 1 4
// 0 2 5
// 1 2 11
// 1 3 9
// 1 4 7
// 2 4 3
// 3 4 13
// 3 5 2
// 4 5 6