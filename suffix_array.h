#ifndef SUFFIX_ARRAY_SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_SUFFIX_ARRAY_H
#include <iostream>
using namespace std;
// Suffix Array class
class suffix_array {
public:
    // char suffix[100];
    int rank[100]; // initial rank
    int temp_rank[100]; // update rank each time when comparing
    int suffix_arr[100]; // contain index for suffix
    int size; // size of each string
    // constructor
    suffix_array(char s[]) ;
    // merge sort O(n log n) to sort suffix array based on rank and step
    void MERGE(int begin, int end, int middle ,int arr[],int step) ; // O(n)
    // call recursively each time divide array into halves and solve each one then combine them
    void Merge_sort(int begin , int end , int arr[],int step) ; // O(n log n)
    // Function to construct the suffix array using prefix doubling
    void ConstructUsingPrefixDoubling() ;
    // Function to compare suffixes based on their ranks and the current step
    bool compare(int i, int j, int step) ;
    // Function to print the suffix array
    void print_suffix_array() ;
};
#endif // SUFFIX_ARRAY_SUFFIX_ARRAY_H