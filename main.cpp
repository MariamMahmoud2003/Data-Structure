#include <iostream>
using namespace std;
int SIZE;
template<typename T>
void heapify_up(T arr[],int i,int n){
    int parent = (i-1)/2;
    if(parent>=0){
        if(arr[i]>arr[parent]){
            swap(arr[i],arr[parent]);
            heapify_up(arr,parent,n);
        }
    }
}
template<typename T>
void insert(T arr[],T key,int n){
    n++;
    arr[n-1]=key;
    heapify_up(arr,n-1,n);
}
template<typename T>
void heapify_down(T arr[],int i, int n){
    int l=2*i+1,r=2*i+2,large=i;
    if(l<n && arr[l]>arr[large])
        large=l;
    if(r<n && arr[r]>arr[large])
        large=r;
    if(large!=i){
        swap(arr[i],arr[large]);
        heapify_down(arr,large,n);
    }
}
template<typename T>
T remove(T arr[],int i, int n){
    T max= arr[i];
    arr[i]=arr[n-1];
    n--;
    heapify_down(arr,i,n);
    return max;
}
template<typename T>
void Build_Max_Heap(T arr[], int n){
    for(int i=n/2;i>=0;--i)
        heapify_down(arr,i,n);
}
template<typename T>
void Heap_sort(T arr[],int n){
    Build_Max_Heap(arr,n);
    for(int i=n-1;i>0;--i){
        swap(arr[0],arr[i]);
        heapify_down(arr,0,i-1);
    }
}
// ___________________________________________________________________
template<typename T>
T Max_priority(T arr[]){
    return arr[0];
}
template<typename T>
T Extract_Max_Priority(T arr[],int n){
    T max=arr[0];
    arr[0]=arr[n-1];
    n--;
    heapify_down(arr,0,n--);
}
template<typename T>
T Key_increase_Priority(T arr[], int i, T key, int n){
    arr[i]=key;
    heapify_up(arr,i,n);
}
template<typename T>
T insert_Max_Priority(T arr[],int n,T key){
    n++;
    arr[n-1]=-100;
    Key_increase_Priority(arr,n-1,key,n);
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    int heap [] = {1,4,7,3,0,34,67,5};
    SIZE = sizeof(heap)/ sizeof(heap[0]) ;
    Build_Max_Heap(heap, sizeof(heap)/ sizeof(heap[0]));
    for(int i = 0; i < sizeof(heap)/ sizeof(heap[0]); ++i)
        cout<<heap[i]<<' ';
    cout<<endl;
    insert(heap,50,sizeof(heap)/ sizeof(heap[0]));
    for(int i = 0; i < sizeof(heap)/ sizeof(heap[0]); ++i)
        cout<<heap[i]<<' ';
    cout<<endl;
    remove(heap,5,sizeof(heap)/ sizeof(heap[0]));
    for(int i = 0; i < sizeof(heap)/ sizeof(heap[0])-1; ++i)
        cout<<heap[i]<<' ';
    cout<<endl;
    Heap_sort(heap,sizeof(heap)/ sizeof(heap[0])-1);
    for(int i = 0; i < sizeof(heap)/ sizeof(heap[0])-1; ++i)
        cout<<heap[i]<<' ';
    cout<<endl;
    return 0;
}
