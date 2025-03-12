#include "suffix_array.h"
#include <iostream>
using namespace std;
// constructor
suffix_array :: suffix_array(char s[]) {
    size=0;
    // to calculate size
    while (s[size] != '\0') {
        ++size;
    }
    // Initialize suffix array and rank
    for (int i = 0; i < size; ++i) {
        // suffix[i]=s[i];
        if (s[i] == '$') { // be the lowest so take 0
            rank[i] = 0;  // '$' gets the lowest rank
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            rank[i] = s[i] - 'a' + 1;  // Characters 'a' to 'z' are mapped to 1 to 26
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            rank[i] = s[i] - 'A' + 27;  // Characters 'A' to 'Z' are mapped to 27 to 52
        }
        suffix_arr[i]=i; // initial order
    }
}
// merge sort O(n log n) to sort suffix array based on rank and step
void suffix_array :: MERGE(int begin, int end, int middle ,int arr[],int step){ // O(n)
    int ls=middle-begin+1,rs=end-middle; // get size of left and right arrays
    int l[ls] , r[rs]; // left and right array
    int i=0; // index point to first item in the left or right array
    for(; i<ls; ++i) // copy items before mid in the left array
        l[i]=arr[i+begin];
    for(i=0; i<rs;++i) // copy items after mid in the right array
        r[i]=arr[i+1+middle];
    i=0; // index point to first item in the left array
    int k=begin,j=0; // index point to begin of original array and other points to begin of right array
    while(i<ls && j<rs){ // compare which one of right or left array will be put now
        if(compare(l[i], r[j], step))
            arr[k++] = l[i++] ; // copy left into original
        else
            arr[k++] = r[j++] ; // copy right into original
    }
    while(i<ls) // copy rest if found from left
        arr[k++] = l[i++]  ;
    while(j<rs) // copy rest if found from right
        arr[k++] = r[j++] ;
}
// call recursively each time divide array into halves and solve each one then combine them
void suffix_array :: Merge_sort(int begin , int end , int arr[],int step){ // O(n log n)
    if(begin>=end) return; // means there is only one item in the array
    int middle= begin+(end-begin) / 2;  // get middle
    // solve left array
    Merge_sort(begin,middle,arr,step); // O(log n)
    // solve right array
    Merge_sort(middle+1,end,arr,step); // O(log n)
    // combine
    MERGE(begin,end,middle,arr,step);
}
// Function to construct the suffix array using prefix doubling
void suffix_array :: ConstructUsingPrefixDoubling() {
    int step = 1; // compare only by using one step as begin
    while (step < size) {
        // Sort suffix array using merge sort that uses compare function
        Merge_sort(0,size-1,suffix_arr,step);
        // Update temporary ranks
        temp_rank[suffix_arr[0]] = 0; // First suffix gets rank 0
        for (int i = 1; i < size; ++i) {
            // compare to each other to get new rank
            if (compare(suffix_arr[i - 1], suffix_arr[i], step)) {
                temp_rank[suffix_arr[i]] = temp_rank[suffix_arr[i - 1]] + 1;
            } else {
                temp_rank[suffix_arr[i]] = temp_rank[suffix_arr[i - 1]];
            }
        }
        // Copy temporary ranks to the rank array
        for(int i=0;i<size;++i)
            rank[i]=temp_rank[i];
        // Double the step
        step *= 2;
    }
}
// Function to compare suffixes based on their ranks and the current step
bool suffix_array :: compare(int i, int j, int step) {
    if (rank[i] != rank[j]) // if not equal check which one is bigger
        return rank[i] < rank[j];
    // if equal find out which one is the smallest according to step
    int ri = i + step < size ? rank[i + step] : -1; // Handle out of bounds
    int rj = j + step < size ? rank[j + step] : -1; // Handle out of bounds
    return ri < rj;
}
// Function to print the suffix array
void suffix_array :: print_suffix_array() {
    for (int i = 0; i < size; ++i) {
        cout << suffix_arr[i] << " ";
    }
    cout << endl<<"-------------------------------";
}
