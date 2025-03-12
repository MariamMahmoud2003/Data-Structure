#include <iostream>
using namespace std;
template<typename T>
// stack based array
class stack_array_based {
    int top,maxsize;
    T * list[];
public:
    void push(T&);
    void pop();
    bool isEmpty();
    bool isFull();
    T Top();
    void initialize();
    void copy(stack_array_based&);
    stack_array_based(stack_array_based&);
    stack_array_based& operator = (stack_array_based&);
    stack_array_based(int);
    ~stack_array_based();
};
template<typename T>
bool stack_array_based<T> ::isEmpty() {
    return top==0;
}
template<typename T>
bool stack_array_based<T> ::isFull() {
    return top==maxsize;
}
template<typename T>
T stack_array_based<T> ::Top() {
    assert(list!=NULL);
    return list[top-1];
}
template<typename T>
void stack_array_based<T> ::initialize() {
    top=0;
}
template<typename T>
void stack_array_based<T> ::push(T& item) {
    if(!isFull()){
        list[top++]=item;
    }
    else{
        cout<<"overflow\n";
    }
}
template<typename T>
void stack_array_based<T> ::pop() {
    if(!isEmpty()){
        top--;
    }
    else{
        cout<<"underflow\n";
    }
}
template<typename T>
void stack_array_based<T> ::copy(stack_array_based & other) {
    if (list!=NULL)
        delete [] list;
    maxsize=other.maxsize;
    top=other.top;
    list=new T [maxsize];
    for(int i=0; i<top; ++i)
        list[i]=other.list[i];
}
template<typename T>
stack_array_based<T>& stack_array_based<T> ::operator = (stack_array_based & other) {
    if(this!=&other)
        copy(other);
    return *this;
}
template<typename T>
stack_array_based<T> ::stack_array_based(int size) {
    if(size <=0){
        cout<<"out boundary and make size 100\n";
        maxsize=100;
    }
    else maxsize=size;
    list=new T[maxsize];
    top=0;
}
template<typename T>
stack_array_based<T> ::stack_array_based(stack_array_based & other) {
    list=NULL;
    copy(other);
}
template<typename T>
stack_array_based<T> ::~stack_array_based() {
    delete [] list;
}
//stack based linked list
template<typename T>
struct nodetype{
    T info;
    nodetype * link;
};
template<typename T>
class linked_stack_based{
    nodetype <T> *top;
public:
    void push(T&);
    void pop();
    bool isEmpty();
    bool isFull();
    T Top();
    void initialize();
    void copy(linked_stack_based&);
    linked_stack_based();
    linked_stack_based(linked_stack_based&);
    linked_stack_based& operator = (linked_stack_based&);
    ~linked_stack_based();
};

template<typename T>
bool linked_stack_based <T> ::isEmpty() {
    return top==NULL;
}
template<typename T>
bool linked_stack_based <T> ::isFull() {
    return false;
}
template<typename T>
T linked_stack_based <T> ::Top() {
    assert(top!=NULL);
    return top-> info;
}
template<typename T>
void linked_stack_based <T> ::initialize() {
    nodetype <T> * temp;
    while(top!=NULL){
        temp=top;
        top=top -> link;
        delete temp;
    }
}
template<typename T>
void linked_stack_based <T> ::push(T & item) {
    nodetype <T> * new_node= new nodetype <T>;
    new_node -> info = item;
    new_node -> link = top;
    top= new_node;
}
template<typename T>
void linked_stack_based <T> :: pop(){
    nodetype <T> * temp;
    temp=top;
    top=top -> link;
    delete temp;
}
template<typename T>
void linked_stack_based<T>::copy(linked_stack_based<T> & other) {
    nodetype <T> *current,*trail,*new_node=new nodetype<T>;
    if(!isEmpty()){
        initialize();
    }
    else{
        current=other.top;
        top ->info = current -> info;
        top ->link = NULL;
        trail=top;
        current = current -> link;
        while(current!= NULL){
            new_node -> info= current -> info;
            new_node=NULL;
            trail -> link= new_node;
            trail=new_node;
            current=current -> link;
        }
    }
}
template<typename T>
linked_stack_based <T> ::linked_stack_based() {
    top=NULL;
}
template<typename T>
linked_stack_based <T> ::linked_stack_based(linked_stack_based<T> & other) {
    top=NULL;
    copy(other);
}
template<typename T>
linked_stack_based <T>& linked_stack_based <T> ::operator=(linked_stack_based<T> & other) {
    if(this != &other)
        copy(other);
    return *this;
}
template<typename T>
linked_stack_based <T> ::~linked_stack_based() {
    initialize();
}
int main (){

    return 0;
}
