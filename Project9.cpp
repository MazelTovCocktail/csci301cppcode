#include <iostream>
#include <random>
using namespace std;

void merge(int*, int, int, int, int&);
void merge_sort(int*, int, int, int&);
void quick_sort(int*, int, int, int&);
int partition(int*, int, int, int&, int&, int&);
void insertion_sort(int*, int, int&);

int main()
{
	//3 arrays for each sorting algorithm
	int array1[5000];
	int array2[5000];
	int array3[5000];
	int array_size, seed;
	char printList = 'n';
	//Input from user.
	cout<<"Size of the array less than 5000: ";
	cin>>array_size;
	cout<<"Random seed integer: ";
	cin>>seed;
	cout<<"Print numbers? y/n ";
	cin>>printList;
	//rand() seed for random numbers.
	srand(seed);
	//This loop sets each array equal to each other.
	int temp;
	for(int i = 0; i<array_size; i++)
	{
		temp = rand() % 5000;
		array1[i] = temp;
		array2[i] = temp;
		array3[i] = temp;
	}
	//Uses insertion sort. Count is by reference.
	int count = 0;
	insertion_sort(array1, array_size, count);
	cout<<"Insertion Sort count: "<<count<<endl;
	//Prints array if user chose 'y'
	if(printList == 'y')
	{
		for(int i = 0; i < array_size; ++i)
			cout<<array1[i]<<" ";
		cout<<"\n"<<endl;
	}
	//Use merge sort.
	count = 0;
	merge_sort(array2, 1, array_size-1, count);
	cout<<"Merge Sort count: "<<count<<endl;
	//output for merge sort array
	if(printList == 'y')
	{
		for(int i = 0; i < array_size; ++i)
			cout<<array2[i]<<" ";
		cout<<"\n"<<endl;
	}
	//use quick sort.
	count = 0;
	quick_sort(array3, 1, array_size-1, count);
	cout<<"Quick Sort count: "<<count<<endl;
	//output for quick sort array
	if(printList == 'y')
	{
		for(int i = 0; i < array_size; ++i)
			cout<<array3[i]<<" ";
		cout<<endl;
	}
	return 0;
}
//Insertion sort function.
void insertion_sort(int a[], int length, int &count)
{
	int temp;  //Basic insertion sort...
	for(int i=1; i < length; i++)
	{
		for(int j=i; j >= 1; j--)
		{
			++count;
			if(a[j] < a[j-1])
			{
				temp = a[j];
				a[j] = a[j-1];
				a[j-1] = temp;
			}
			else
				break;
		}
		++count;
	}
}
//merge sort recursive function
void merge_sort(int a[], int low, int high, int &count)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		merge_sort(a, low, mid, count); //from low to mid
		merge_sort(a, mid+1, high, count);//from mid to high
		merge(a, low, mid, high, count); //recursion...
	}
}

void merge(int a[], int low, int mid, int high, int &count)
{
	int b[5000];
	int i1, i2, index;
	//for loop to copy a[] into b[]
	for (size_t i=low; i<= high; ++i)
	{
		b[i] = a[i];
		++count;
	}
	//set i1, i2, and index
    i1 = low;
    i2 = mid+1;
    index = low;
    while ( i1 <= mid && i2 <= high )
    {
		if ( b[i1] < b[i2] )
			a[index++] = b[i1++];
		else //b[i2] >= b[i1]
        	a[index++] = b[i2++];
        ++count;
    }
    
    while ( i1 <= mid )
    {
		a[index++] = b[i1++];
		++count;
	}

    while ( i2 <= high )
    {
		a[index++] = b[i2++];
		++count;
	}
}
//quick sort recursive function
void quick_sort(int a[], int low, int high, int& count)
{
	int i, j;
    if ( low < high )
    {
		partition ( a, low, high, i, j, count);
		quick_sort ( a, low, i, count );
    	quick_sort ( a, j, high, count );
    }
}

int partition(int a[], int low, int high, int &i, int &j, int& count)
{
	int pivot = a[low];
	int lastS1 = low - 1;
    int firstU = low;
    int firstS3 = high + 1;
    int temp;

    while ( firstU < firstS3 )
    {
    	if ( a[firstU] < pivot ) // S1
		{
        	++lastS1;
        	//swap...
        	temp = a[firstU];
        	a[firstU] = a[lastS1];
        	a[lastS1] = temp;
        	++firstU;
		}
    	else if ( a[firstU] == pivot ) // S2
    	{
        	++firstU;
        }
		else  // a[firstU] > pivot  -  S3
      	{
        	--firstS3;
        	//swap values
        	temp = a[firstU];
        	a[firstU] = a[firstS3];
        	a[firstS3] = temp;
		}
		++count;
    }
    i = lastS1;
    j = firstS3;
}
