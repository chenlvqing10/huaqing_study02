#include<stdio.h>

/*Merge Sort*/

void Merge(int arr[], int temp[], int left, int mid, int right)
{
	int i = left, j = mid + 1;
	int k = left;
	while ((i <= mid) && (j <= right))//the range is [left mid] [mid+1 right]
	{
		if (arr[i]<arr[j])//each time compare the number what point to the array head
			temp[k++] = arr[i++];//put the mix value to temp array(left sequence)
		else
			temp[k++] = arr[j++];//put the mix value to temp array(right sequence)

	}

	while(i <= mid)//set the value to temp(in left)
		temp[k++] = arr[i++];
	while(j <= right)//set the  value to temp(in right)
	{
		temp[k++] = arr[j++];
	}

	//copy the temp[] to arr[]
	for (i = left; i <=right; i++)
		arr[i] = temp[i];
}
void MergeSort(int arr[],int left,int right,int temp[])
{
	//the temp array


	if (left < right)
	{
		int mid = (left+right) / 2;
		MergeSort(arr, left, mid,temp);//divide and sort the left sequence(recursive)
		MergeSort(arr, mid + 1, right, temp);//divide and sort the right sequence(recursive)
		Merge(arr, temp,left,mid, right);//first merge the left sequence ,then merge the right sequence,lsat merge the all sequence
	}
}
void Merge_twoarr(int arr1[],int arr2[], int temp[], int left, int mid, int right)
{
	int i = left, j = left;
	int k = left;
	while ((i <= mid) && (j <= right))//the range is [left mid] [mid+1 right]
	{
		if (arr1[i] < arr2[j])//each time compare the number what point to the array head
			temp[k++] = arr1[i++];//put the mix value to temp array(left sequence)
		else
			temp[k++] = arr2[j++];//put the mix value to temp array(right sequence)

	}

	while (i <= mid)//set the value to temp(in left)
		temp[k++] = arr1[i++];
	while (j <= right)//set the  value to temp(in right)
	{
		temp[k++] = arr2[j++];
	}
}
int main()
{
	/*
	   int size_a,a[100];
	   int temp[100];

	   printf("Please input a int array size:");
	   scanf("%d",&size_a);

	   printf("Please input the array:");
	   for (int i=0;i<size_a;i++)
	   scanf("%d",&a[i]);

	   printf("the sequence Before:\n");
	   for (int i = 0; i < size_a; i++)
	   printf("%d  ", a[i]);
	   printf("\n");

	//call the mergersort function to sort a
	MergeSort(a,0, size_a -1,temp);

	printf("the sequence After:\n");
	for (int i = 0; i < size_a; i++)
	printf("%d ", a[i]);
	*/
	//int a[5] = { 1,13,5,9,8 };
	//int b[7] = { 12,2,7,4,10,3,11};
	int a[100], b[100];
	int c[100];
	int len_a,len_b;
	printf("Please input first array's size:");
	scanf("%d",&len_a);
	printf("Please input first array's value:");
	for (int i=0;i<len_a;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("Please input second array's size:");
	scanf("%d", &len_b);
	printf("Please input second array's value:");
	for (int i = 0; i < len_b; i++)
	{
		scanf("%d", &b[i]);
	}
	//int len_a = sizeof(a) / sizeof(a[0]);
	//int len_b = sizeof(b) / sizeof(b[0]);


	//call the mergersort function to sort a
	MergeSort(a, 0, len_a-1, c);
	MergeSort(b, 0, len_b-1, c);
	printf("the sequence After for a:\n");
	for (int i = 0; i < len_a; i++)
		printf("%d ", a[i]);
	printf("\n");
	printf("the sequence After for b:\n");
	for (int i = 0; i < len_b; i++)
		printf("%d ", b[i]);
	printf("\n");

	Merge_twoarr(a, b, c, 0, len_a - 1, len_b - 1);
	printf("the sequence After for b:\n");
	for (int i = 0; i < len_a+len_b; i++)
		printf("%d ", c[i]);
	printf("\n");

	return 0;
}
