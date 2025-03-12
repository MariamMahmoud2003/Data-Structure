//
// Created by Lenovo on 4/18/2024.
//

#ifndef BUBBLE_SORT_IMPLEMENTATION_H
#define BUBBLE_SORT_IMPLEMENTATION_H


#include <string>
using namespace std;class SIngleLinkedList {
    string name;
    double gpa;
    int id;
public:
    SIngleLinkedList();
    const string &getName() const;
    void setName(const string &name);
    double getGpa() const;
    void setGpa(double gpa);
    int getId() const;
    void setId(int id);
    double operator < (SIngleLinkedList& other);
    bool operator > (SIngleLinkedList& other);
    string print();
};


#endif //BUBBLE_SORT_IMPLEMENTATION_H
