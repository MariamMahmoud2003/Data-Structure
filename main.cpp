// Mariam Mahmoud Ibrahim 20221207
#include <iostream>
#include <cassert>
using namespace std;
template<typename element_Type>
// single node
struct node_type{
    // for data
    element_Type info;
    // for address to next node
    node_type * link;
};
template<typename element_Type>
class Queue{
    node_type <element_Type> * first,* Rear /*last*/;
    int size;
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
    void clear ();// O(n)
    // print items
    void print ();// O(n)
    // default constructor
    Queue ();// O(1)
    // destructor
    ~Queue ();// O(n)
};
template<typename element_Type>
void Queue <element_Type> :: enqueue (element_Type element) {
    // make external node
    auto /*node_type <element_Type>*/ * new_node = new node_type <element_Type>;
    // initialize its info with item value
    new_node -> info = element;
    new_node -> link = nullptr;
    if(first == nullptr){// if queue is empty
        first = new_node;
        Rear = new_node;
    }
    else{// add at end by making link of last item point to new_node then
        // make Rear _a pointer for last item_ point to new_node
        Rear -> link = new_node;
        Rear = new_node;
    }
    // increment size
    size ++;
}
template<typename element_Type>
element_Type Queue <element_Type> :: dequeue () {
    if(isEmpty()) {// empty queue
        cout << "UNDERFLOW\n";
        return -1;
    }
    else{// delete from begin
        // get first item
        node_type <element_Type> * temp = first;
        // make first point to next item
        first = first -> link;
        // get item value that will be deleted
        element_Type item = temp -> info;
        // delete temp
        delete temp;
        // if first is null means queue becomes empty
        if(first == nullptr)
            // so make Rear null too
            Rear = nullptr;
        // decrement size
        size --;
        // return item
        return item;
    }
}
template<typename element_Type>
element_Type Queue <element_Type> :: First () {
    assert(!isEmpty());
    // get value of first node
    return first -> info;
}
template<typename element_Type>
bool Queue <element_Type> :: isEmpty () {
    // return false if one of constrains false
    return ((first == nullptr || size == 0) ? bool(true) : bool(false));
}
template<typename element_Type>
int Queue <element_Type> :: queueSize () {
    // we can get by looping on the queue and count items till
    // reach null _this if I don't have size attribute_ and its complexity will be O(n)
    return size;
}
template<typename element_Type>
void Queue <element_Type> :: clear () {
    node_type <element_Type> * temp;
    // loop on queue till reach its end
    while(first != nullptr){
        // make temp point to first node
        temp = first;
        // make first go to next node (traversal)
        first = first -> link;
        // delete temp to avoid memory leakage
        delete temp;
    }
    // make all thing refer that it's empty
    Rear = nullptr;
    size=0;
}
template<typename element_Type>
void Queue <element_Type> :: print () {
    node_type <element_Type> * current;
    // to get each node and its number ZERO indexed
    int i = 0;
    current = first;
    while(current != nullptr){
        // print information
        cout << "Node number " <<  i << " is " << current->info << '\n';
        // go to next node
        current = current -> link;
        i ++;
    }
}
template<typename element_Type>
Queue <element_Type> :: Queue () {
    // initialize attributes
    size = 0;
    Rear = nullptr;
    first = nullptr;
}
template<typename element_Type>
Queue <element_Type> :: ~Queue () {
    clear ();
}
int main() {
    Queue <int> Q;
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
    return 0;
}