#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

//swaps two elements of an array at index i and j
void swap(int * arr,int i,int j)
{
	int temp;
	temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
}

//declares a structure having a name field and cgpa field
typedef struct student{
	char * sname;
	int cgpa_marks;
}student;

student * records=NULL;
//displays records roll no. wise in "NAME MARKS" format
void displayRecords(student * arr,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%s\t%d\n",arr[i].sname,arr[i].cgpa_marks);
	}
	printf("\n");
}

//displays the values of an array
void displayprQ(int * arr,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d\t",arr[i]);
	}
	printf("\n");
}

//copies the ith index of priority queue to the kth index of the hash table, where k is the value at ith index of priority queue
void updateHash(int * hash,int * priority_queue,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		hash[priority_queue[i]]=i;
	}
}

//finds the maximum node between parent and its two children, and swaps and recursively calls itself
void Max_heapify( int * priority_queue, int * hash, int prQ_indx, int n)
{
	int largest=prQ_indx;
	int left=prQ_indx*2+1;
	int right=prQ_indx*2+2;
	if(left<n && records[priority_queue[largest]].cgpa_marks<records[priority_queue[left]].cgpa_marks)
	{
		largest=left;
	}
	if(right<n && records[priority_queue[largest]].cgpa_marks<records[priority_queue[right]].cgpa_marks)
	{
		largest=right;
	}
	if(largest!=prQ_indx)
	{
		swap(priority_queue,largest,prQ_indx);
		Max_heapify(priority_queue,hash,largest,n);
		updateHash(hash,priority_queue,n);
	}
	
}

//calls heapify at the nodes which has atleast one child node, from bottom to top
void Build_priorityQ( int * priority_queue, int * hash, int n)
{
	int i;
	for(i=n/2-1;i>=0;i--)
	{
		Max_heapify(priority_queue,hash,i,n);
	}
}

//updates the cgpa of the roll no. taken as input by the user
void heap_increase_key( int priority_queue[ ], int hash[ ], int prQ_indx, int n)
{
	int cgpa;
	printf("Enter the new cgpa:");
	scanf("%d",&cgpa);
	records[priority_queue[prQ_indx]].cgpa_marks=cgpa;
	Build_priorityQ(priority_queue,hash,n);
}

//inserts new node in the priority Max-heap
void Enqueue_priorityQ(int * priority_queue,int * hash,int new_roll,int n)
{
    char name[100];
    int cgpa;
    printf("Enter the student name:");
    scanf("%s",name);
    printf("Enter the cgpa:");
    scanf("%d",&cgpa);
    student * stud=(student *)malloc(sizeof(student));
    stud->sname=name;
    stud->cgpa_marks=cgpa;
    priority_queue[n++]=new_roll;
    records[new_roll].sname=name;
    records[new_roll].cgpa_marks=cgpa;
    Build_priorityQ(priority_queue,hash,n);
    updateHash(hash,priority_queue,n);
    displayRecords(records,++new_roll);
    displayprQ(priority_queue,n);
}

//removes the node with the maximum marks
int Dequeue_priorityQ(int * priority_queue,int * hash,int n)
{
    n--;
    int root=priority_queue[0];
    swap(priority_queue,0,n);
    displayprQ(priority_queue,n);
    Build_priorityQ(priority_queue,hash,n);
    displayprQ(priority_queue,n);
    return root;
}


int main()
{
	char * name;
	int opt,cgpa,len=5,new_roll,roll,n=5;
	records=(student *)malloc(sizeof(student)*100);
	records[0].sname="A";
	records[0].cgpa_marks=90;

	records[1].sname="B";
	records[1].cgpa_marks=69;

	records[2].sname="C";
	records[2].cgpa_marks=70;

	records[3].sname="D";
	records[3].cgpa_marks=85;

	records[4].sname="E";
	records[4].cgpa_marks=100;

	int i;
	int * priority_queue=(int *)malloc(sizeof(int)*100);
	int * hash=(int *)malloc(sizeof(int)*100);
	for(i=0;i<len;i++)
	{
		priority_queue[i]=i;
		hash[i]=i;
	}

	Build_priorityQ(priority_queue,hash,5);

	while(1)
	{
		printf("\nChoose from the following options:\n");
		printf("1.Enqueue a Student\n2.Dequeue student having max cgpa\n");
		printf("3.Increase CGPA of a student\n4.Decrease CGPA of a student\n");
		printf("5.Show Records Array\n6.Show Priority Max-Heap\n7.Show Hash Array\n8.Exit\n");
		printf("Enter your option: ");
		scanf("%d",&opt);
		if(opt==1)
		{
            // printf("\n%d %d\n",n,len);
			Enqueue_priorityQ(priority_queue,hash,n,len);
            n++;
            len++;
            // printf("\n%d %d\n",n,len);
		}
		else if(opt==2)
		{
            if(len==0){
                printf("No more elements to dequeue!\n");
                continue;
            }
			int root=Dequeue_priorityQ(priority_queue,hash,len);
            len--;
            printf("The student %s has highest cgpa of %d is Roll No. %d\n",records[root].sname,records[root].cgpa_marks,root);
		}
		else if(opt==3 || opt==4)
		{
			printf("Enter the Roll No.:");
			scanf("%d",&roll);
			updateHash(hash,priority_queue,len);
			int prQ_indx=hash[roll];
			heap_increase_key(priority_queue,hash,prQ_indx,len);
		}
		else if(opt==5)
		{
			printf("The records are\n");
			displayRecords(records,n);
			
		}
		else if(opt==6)
		{
			printf("The priority Max-Heap is\n");
			displayprQ(priority_queue,len);
		}
		else if(opt==7)
		{
			printf("The hash array is\n");
			displayprQ(hash,n);
		}
		else if(opt==8)
		{
			exit(1);
		}
		else
		{
			printf("Enter a valid option!\n");
		}
	}
	return 0;
}
