// Mariam Mahmoud Ibrahim 20221207
#include <iostream>
#include <cassert>
using namespace std;
template<typename element_Type>
class Queue{
    int size,first,Rear,MaxSize;
    element_Type * list;
public:
    // insert at end
    void enqueue(element_Type);// O(1)
    // delete from begin
    element_Type dequeue ();// O(1)
    // get first item
    element_Type First ();// O(1)
    // check if empty
    bool isEmpty ();// O(1)
    // get size
    int queueSize ();// O(1)
    // initialize queue
    void clear ();// O(1)
    // print items
    void print ();// O(n)
    // parameterized constructor
    Queue (int);// O(1)
    // destructor
    ~Queue ();// O(n)
};
template<typename element_Type>
void Queue <element_Type> :: enqueue (element_Type element) {
    // if full can not insert
    if(size == MaxSize)
        cout << "Overflow\n";
    else{
        // get the next empty position that will insert in as it is circular array by changing place of Rear
        Rear = (Rear + 1) % MaxSize;
        // insert it into queue
        list [Rear] = element;
        // increment size
        size ++;
    }
}
template<typename element_Type>
element_Type Queue <element_Type> :: dequeue () {
    // if not empty can delete
    if(!isEmpty()){
        // decrement size
        size --;
        // get element that will be deleted
        element_Type element = First();
        // get the next position after the deleted value as it is circular array by changing place of first
        first = (first + 1) % MaxSize;
        // return deleted element
        return element;
    }
    // if empty can not delete
    else
        cout << "underflow\n";
    return -1;
}
template<typename element_Type>
element_Type Queue <element_Type> :: First () {
    // make sure that list has allocated in memory well
    assert(list != nullptr);
    return list [first];
}
template<typename element_Type>
bool Queue <element_Type> :: isEmpty () {
    // no element in queue
    return size == 0;
}
template<typename element_Type>
int Queue <element_Type> :: queueSize () {
    // current size
    return size;
}
template<typename element_Type>
void Queue <element_Type> :: clear () {
    // make every thing refer that it is empty again
    size = 0;
    first = 0;
    // as it point at last
    Rear = MaxSize - 1;
}
template<typename element_Type>
void Queue <element_Type> :: print () {
    // loop on queue begin from first because it's not always begin from 0 as its circular and end at rear last element in queue as its circular
    for(int i=first; i<Rear+1 && (size != 0) ;++i){
        // print index and content (to make always first begin with 0 and increment by 1 make current index - first that point to the smallest index)
        cout << "Node number " << i - first << " is " << list [i] << endl;
    }
}
template<typename element_Type>
Queue <element_Type> :: Queue (int si) {
    // initialize private attributes
    if(si <= 0){
        cout << "error size can not be negative we will set max size to 200\n";
        MaxSize = 200;
    }
    else
        MaxSize = si;
    size = 0;
    // initialize pointer to point to an array in memory (dynamic allocation)
    list = new element_Type [MaxSize];
    first = 0;
    Rear = MaxSize - 1;
}
template<typename element_Type>
Queue <element_Type> :: ~Queue () {
    delete [] list;
}
int main() {
    Queue <int> Q(7);
    cout<<"Empty "<<boolalpha<<(Q.isEmpty())<<endl;
    cout<<"---------------\n";
    int t=5;
    Q.enqueue(t);
    Q.enqueue(6);
    Q.enqueue(7);
    Q.enqueue(10);
    Q.enqueue(1);
    Q.enqueue(20);
    Q.print();
    cout<<"---------------\n";
    cout<<"deleted value is "<<Q.dequeue()<<endl;
    cout<<"---------------\n";
    Q.print();
    cout<<"---------------\n";
    cout<<"First element is "<<Q.First()<<endl;
    cout<<"---------------\n";
    cout<<"deleted value is "<<Q.dequeue()<<endl;
    cout<<"---------------\n";
    Q.print();
    cout<<"---------------\n";
    cout<<"Empty "<<Q.isEmpty()<<endl;
    cout<<"---------------\n";
    cout<<"Size of queue is "<<Q.queueSize()<<endl;
    cout<<"---------------\n";
    Q.clear();
    cout<<"Size now "<<Q.queueSize()<<endl;
    cout<<"---------------\n";
    cout<<"Empty "<<Q.isEmpty()<<endl;
    cout<<"---------------\n";
    cout<<"deleted element "<<Q.dequeue()<<endl;
    cout<<"---------------\n";
    Q.print();
    cout<<"---------------\n";
    Q.enqueue(t);
    Q.enqueue(6);
    Q.enqueue(7);
    Q.enqueue(10);
    Q.enqueue(1);
    Q.enqueue(20);
    Q.print();
    cout<<"---------------\n";
    Q.print();
    cout<<"---------------\n";
    return 0;
}