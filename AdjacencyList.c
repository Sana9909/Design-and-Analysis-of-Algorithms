//Weighted undirected graph's adjacency list

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int vertex;
	int weight;
	struct node * next;
}node;

void display(node ** arr, int n)
{
	int i, j;
	node * head;
	printf("The Adjacency List is:\n");
	for(i=0; i<n; i++)
	{
		printf("V%d : ",i);
		head=arr[i];
		while(head!=NULL)
		{
			printf("vertex:%d,weight:%d --> ",head->vertex,head->weight);
			head=head->next;
		}
		printf("NULL\n");
	}
}

node * insertBeg(node * head, int v, int w)
{
	node * p=(node *)malloc(sizeof(node));
	p->vertex=v;
	p->weight=w;
	if(head!=NULL)
	{
		p->next=head;
	}
	head=p;
	return head;
}
		
	
int main()
{
	int u, v, w, n, i;
	FILE * fp;
	node ** arr;
	fp=fopen("./edgeList.txt", "r");
	if(fp!=NULL)
	{
		fscanf(fp,"%d\n", &n);
		arr=(node **)malloc(sizeof(node *)*n);
		for(i=0; i<n; i++)
		{
			arr[i]=NULL;
		}
		while(!feof(fp))
		{
			fscanf(fp,"%d %d %d\n", &u, &v, &w);
			arr[u]=insertBeg(arr[u],v,w);
			arr[v]=insertBeg(arr[v],u,w);			
		}
		fclose(fp);
		display(arr,n);
	}
	else
	{
		printf("Error in opening file!\n");
	}
	for(i=0; i<n; i++)
	{
		free(arr[i]);
	}
	free(arr);
	return 0;	
}
