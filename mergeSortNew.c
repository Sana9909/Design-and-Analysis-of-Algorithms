#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <limits.h>

int comparisons=0;

void display(int * arr,int n)
{
	int i;
	printf("The array is:\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",arr[i]);
	}
	printf("\n\n");
}

void swap(int * arr,int i,int j)
{
	int temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
}

void generate_random(int n)
{
	FILE * fp;
	fp=fopen("./array.txt","w");
	srand(time(NULL)); 
	int i;
	int * arr=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		arr[i]=i+1;
	}
	for(i=n-1;i>=0;i--)
	{
		int index=rand()%n;
		swap(arr,i,index);
	}
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%d ",arr[i]);
	}
	printf("The random sequence has been successfully generated!\n");
	fclose(fp);
}		
	
void merge(int * arr,int p,int q,int r)
{
	int n1,n2,i,j,k;
	n1=q-p+1;
	n2=r-q;
	int * leftArray=(int *)malloc(sizeof(int)*n1);
	int * rightArray=(int *)malloc(sizeof(int)*n2);
	for(i=0;i<n1;i++)
	{
		leftArray[i]=arr[p+i];
	}
	for(j=0;j<n2;j++)
	{
		rightArray[j]=arr[q+j+1];
	}
	i=0;
	j=0;
	k=p;
	while(i<n1 && j<n2)
	{
		comparisons++;
		if(leftArray[i]<rightArray[j])
		{
			arr[k]=leftArray[i];
			i++;
		}
		else
		{
			arr[k]=rightArray[j];
			j++;
		}
		k++;
	}
	while(i<n1)
	{
		arr[k]=leftArray[i++];
		k++;
	}
	while(j<n2)
	{
		arr[k]=rightArray[j++];
		k++;
	}
	
}

void mergeSort(int * arr,int p,int r)
{
	if(p<r)
	{
		int q=(p+r)/2;
		mergeSort(arr,p,q);
		mergeSort(arr,q+1,r);
		merge(arr,p,q,r);
	}
}

int main()
{
	FILE * fp;
	int n,num,i=0;
	fp=fopen("./array.txt","r");
	printf("Enter the number of elements:");
	scanf("%d",&n);
	if(fp==NULL)
	{
		printf("Error in opening the file!\n");
		return 1;
	}
	else
	{
		int * arr=(int *)malloc(sizeof(int)*n);
		generate_random(n);
		while(!feof(fp))
		{
			fscanf(fp,"%d ",&arr[i]);
			i++;
		}
		display(arr,n);
		mergeSort(arr,0,n-1);
		display(arr,n);
	}
	printf("The number of comparisons is: %d\n",comparisons);
	fclose(fp);
	return 0;
}









