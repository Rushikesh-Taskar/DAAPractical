#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
// this function mearge two array in new array with sorted mannner
// and again copy merge array into original array
int merge(int *A,int mid,int low ,int high)
{
    int B[100];
    int i,j,k;
    i=low;
    j=mid+1; 
    k=low;
    while(i<=mid && j<=high)    
    {
        if(A[i]<A[j])         //A[i]>A[j] descending
        {
            B[k]=A[i];
            i++;
            k++;
        }
        else if(A[i]>A[j])      //A[i]<A[j] descending
        {
            B[k]=A[j];
            j++;
            k++;
        }
    }
    while(i<=mid)
    {
        B[k]=A[i];
        i++;
        k++;
    }
    while(j<=high)
    {
        B[k]=A[j];
        j++;
        k++;
    }
    for(int i=low;i<=high;i++)
    {
        A[i]=B[i];
    }
    return 0;
}
// this is recursive call function 
// this function divide array into two different array 
// and call merge function to merge that two array in sorted manner
int merge_sort(int *A,int low,int high)
{
   int mid;
   if(high>low)
   {
   mid=(low+high)/2;
   merge_sort(A,low ,mid);
   merge_sort(A,mid+1,high);
   merge(A,mid,low,high);
   }
   return 0;
}


int print(int *Arr ,int n)
{
   for(int i=0;i<n;i++)
   {
       cout<<Arr[i]<<" ";
   }cout<<endl;
   return 0;
}
int main()
{
    auto start = high_resolution_clock::now();
    int n;
    cout<<"enter size of array"<<endl;
    cin>>n;
    int Arr[n];
    for(int i=0;i<n;i++)
    {
        Arr[i]=rand()%1000;
    }
    cout<<"Original array look like"<<endl;
    print(Arr , n);
    cout<<"array in ascending order"<<endl;
    merge_sort(Arr,0,n-1);
    print(Arr , n);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
   cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
}
