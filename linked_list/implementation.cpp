//
// Created by Lenovo on 4/18/2024.
//
#include <iostream>
#include "implementation.h"
using namespace std;
SIngleLinkedList::SIngleLinkedList(){
}
const string &SIngleLinkedList::getName() const {
    return name;}

void SIngleLinkedList::setName(const string &name) {    SIngleLinkedList::name = name;
}
double SIngleLinkedList::getGpa() const {    return gpa;
}
void SIngleLinkedList::setGpa(double gpa) {    SIngleLinkedList::gpa = gpa;
}
int SIngleLinkedList::getId() const {    return id;
}
void SIngleLinkedList::setId(int id) {    SIngleLinkedList::id = id;
}
double SIngleLinkedList::operator < (SIngleLinkedList &other) {    return gpa < other.gpa ;
}
bool SIngleLinkedList::operator > (SIngleLinkedList &other) {
    return other.name > name;
}
string SIngleLinkedList::print(){    return name + "\n" + to_string(id) + "\n"  + to_string(gpa);
}