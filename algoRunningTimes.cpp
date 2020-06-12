#include <iostream>
#include <climits>
#include <chrono>
#include <cstdlib>

#define t_micros std::chrono::microseconds


void quickSort(int  arr[], int n); //Wrapping Function for quickSort
void quickSort(int  arr[],int start,int end); //Actual quickSort
void mergeSort(int arr[],int n); //Wrapping function for mergeSort
void mergeSort(int arr[],int start,int end); //Actual mergeSort()
void insertionSort(int  arr[],int n); // insertionSort()


//Helping Functions 
void merge(int arr[], int start,int mid, int end);
int partition(int  arr[] ,int start,int end);
void swap(int arr[],int a,int b);


//The function to calculate the running time of the function
//That it gets as an argument
t_micros runningTime (int arr[],int arr_size,void (*pf) (int arr[] ,int n));


void initiallize(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=rand()%n+1;
    }
    
}


int main() {
    using namespace std;
    const int ARR_SIZE=10000;
    
    int arr_1[ARR_SIZE];
   
    
    initiallize(arr_1,ARR_SIZE);
    
    
    
    //Testing the sorting algorithms with 3 different functions
    //Using pointers to functions
    //Printing the execution times in milliseconds
    
    cout<<"Testing mergeSort"<<endl;
    cout<<"Time taken(in microseconds):  "<<runningTime(arr_1,ARR_SIZE,mergeSort).count()<<endl;
    
    //Reinitiallizeing the array
    initiallize(arr_1,ARR_SIZE);
    
    //Test for quickSort
    
    cout<<"Testing quickSort"<<endl;
    cout<<"Time taken(in microseconds):  "<<runningTime(arr_1,ARR_SIZE,quickSort).count()<<endl;
    
    
    //Reinitiallizeing the array
    initiallize(arr_1,ARR_SIZE);
    
    //Test for insertionSort
    cout<<"Testing insertionSort"<<endl;
    cout<<"Time taken(in microseconds):  "<<runningTime(arr_1,ARR_SIZE,insertionSort).count()<<endl;
    
    
    
    
}

//Implementation of quickSort

void swap(int arr[],int a,int b){
    int temp=arr[a];
    arr[a]=arr[b];
    arr[b]=temp;
}


void quickSort(int arr[],int n){
    quickSort(arr,0,n-1);
}
void quickSort(int arr[],int start,int end){
    if(start<end){
        int part=partition(arr,start,end);
        quickSort(arr,start,part-1);
        quickSort(arr,part+1,end);
    }
}
int partition(int arr[] ,int start,int end ){
    int pivot=arr[start];
    int pInd=start;
    int i;
    for(i=start+1;i<=end;i++){
        if(arr[i]<pivot){
            pInd++;
            swap(arr,pInd,i);
        }
    }
    swap(arr,pInd,start);
    return pInd;
    
}

//Implementation of mergeSort

void mergeSort(int arr[],int n){
    mergeSort(arr,0,n-1);
}

void mergeSort(int arr[],int start,int end){
    if(start<end){
        int mid=(start+end)/2;
        mergeSort(arr,start,mid);
        mergeSort(arr,mid+1,end);
        merge(arr,start,mid,end);
    }
}

void merge(int arr[], int start, int mid,int end){
    int length1=mid-start+1;     //mid is included first array
    int length2=end-mid;        
    int *left = new int [length1+1];
    int *right= new int [length2+1];
    left[length1]=INT_MAX; 
    right[length2]=INT_MAX;
    //Filling the arrays
    for(int i=0;i<length1;i++){
        left[i]=arr[start+i];
    }
    for(int i=0;i<length2;i++){
        right[i]=arr[mid+1+i];
    }
    
    //Merging
    int l=0;
    int r=0;
    
    for(int i=start;i<=end;i++){
        if(left[l]<right[r]){
            arr[i]=left[l++];
        }
        else{
            arr[i]=right[r++];
        }
    }
    delete [] left;
    delete [] right;
}


//Implementation of insertion Sort

void insertionSort(int arr[] ,int n){
    using namespace std;
    if(n==0||n==1)return;
    
    for(int i=1;i<n;i++){
        int curr=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>=curr){
            arr[j+1]=arr[j];
            
            j--;
            
        }
        
        arr[j+1]=curr;
    }
    
}

t_micros runningTime (int arr[],int arr_size,void (*pf) (int arr[] ,int n)){
    using std::cout;
    
    auto t_start=std::chrono::high_resolution_clock::now();
    pf(arr,arr_size);
    auto t_end=std::chrono::high_resolution_clock::now();
    
    
    
    return std::chrono::duration_cast<t_micros>(t_end-t_start);
}

