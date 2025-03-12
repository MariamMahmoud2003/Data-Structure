#include <iostream>
#include <cmath>
using namespace std;
template<typename T>
class BTnode{
    T info;
    BTnode * right;
    BTnode * left;
public:
    BTnode(){
        info = 0;
        right = nullptr;
        left = nullptr;
    }
};
template<typename T>
class Binary_Tree{
    BTnode <T> * Root;
protected:
    Binary_Tree();
    int height(BTnode <T> *);
    int get_height();
    int count();
    int leaves();
    void copy(BTnode <T> *,BTnode <T> *);
    void traverse();
    void traversal (BTnode <T> *);
    bool isEmpty();
    void destroy(BTnode <T> *);
    void destroy();
    Binary_Tree(Binary_Tree <T> &);
    ~Binary_Tree();
    Binary_Tree <T> &  operator = (Binary_Tree <T> &&);
};

template<typename T>
Binary_Tree <T> ::Binary_Tree() {
    Root = nullptr;
}
template<typename T>
Binary_Tree <T> ::~Binary_Tree() {
    destroy();
}
template<typename T>
int Binary_Tree<T>::height(BTnode <T> * p) {
    if(p != nullptr){
        return 1 + max (height(p -> right),height(p -> left));
    }
    return 0;
}
template<typename T>
int Binary_Tree<T>::get_height() {
    return height(Root);
}
template<typename T>
int Binary_Tree <T> ::count() {
    int h = height ();
    return int (pow(2,h) - 1);
}
template<typename T>
int Binary_Tree <T> ::leaves() {
    int h = height ();
    return int (pow(2,h - 1));
}
template<typename T>
void Binary_Tree <T> ::copy(BTnode <T> * root,BTnode<T> * other) {
    if(other == nullptr){
        root = nullptr;
    }
    else{
        if (root != nullptr)
            destroy(root);
        root = new BTnode <T>;
        root -> info = other -> info;
        copy (root -> right,other -> right);
        copy (root -> left,other -> left);
    }
}

template<typename T>
void Binary_Tree <T> ::traverse() {
    traversal(Root);
}
template<typename T>
void Binary_Tree <T> ::traversal(BTnode <T> * p) {
    cout<<"1.inorder\n2.preorder\n3.postorder\n";
    int n;
    cin>>n;
    switch (n) {
        case 1:
            traversal(p -> left);
            cout<<p -> info<<" ";
            traversal (p -> right);
            break;
        case 2:
            cout<<p -> info<<" ";
            traversal(p -> left);
            traversal (p -> right);
            break;
        case 3:
            traversal(p -> left);
            traversal (p -> right);
            cout<<p -> info<<" ";
            break;
    }
}
template <typename T>
bool Binary_Tree <T> ::isEmpty() {
    return Root == nullptr;
}
template <typename T>
void Binary_Tree <T> ::destroy(BTnode<T> * p) {
    if(p != nullptr){
        destroy(p -> left);
        destroy(p -> right);
        delete p;
        p = nullptr;
    }
}
template <typename T>
void Binary_Tree <T> ::destroy() {
    destroy (Root);
}
template <typename T>
Binary_Tree <T> ::Binary_Tree(Binary_Tree<T> & other) {
    copy(Root,other);
}
template<typename T>
Binary_Tree <T> & Binary_Tree <T> ::operator =(Binary_Tree<T> &&other) {
    if(this != other){
        copy(Root,other);
    }
    return * this;
}
//____________________________________________________
template<typename T>
class Binary_Search_Tree :protected Binary_Tree <T>{
    BTnode <T> * Root;
public:
    Binary_Search_Tree();
    void insert(T);
    void removes(T);
    void remove(BTnode <T> *);
    bool search (T);
};

template<typename T>
Binary_Search_Tree <T> ::Binary_Search_Tree() {
    Root = nullptr;
}
template <typename T>
void Binary_Search_Tree <T> ::insert(T item) {
    auto * new_node = new BTnode <T>;
    BTnode <T> * current =Root , * prev;
    new_node -> info =item;
    new_node -> right = nullptr;
    new_node -> left = nullptr;
    if(Root == nullptr)
        Root = new_node;
    else {
        bool found = false;
        while (current != nullptr) {
            prev = current;
            if (current->info == item) {
                cout << "item already found!\n";
                found = true;
                break;
            } else if (current->info > item)
                current = current->left;
            else
                current = current->right;
        }
        if (current == Root)
            Root = new_node;
        if (!found) {
            if (prev->info > item)
                prev->left = new_node;
            else
                prev->right = new_node;
        }
    }
}

template<typename T>
void Binary_Search_Tree <T>::removes(T item) {
    BTnode<T> *current = Root, *prev;
    if (Binary_Tree <T>:: isEmpty()) {
        cout << "empty\n";
    } else {
        bool found = false;
        while (current != nullptr && !found) {
            if (current->info == item) {
                found = true;
            } else if (current->info > item) {
                prev = current;
                current = current->left;
            }
            else
                prev = current;
                current = current->right;
        }
        if(found)
            remove(current);
    }
}

template<typename T>
void Binary_Search_Tree<T> ::remove(BTnode<T> * p) {
    BTnode <T> * temp, * prev ;
    if(p -> right == nullptr && p -> left == nullptr){
        temp = p;
        p = nullptr;
        delete temp;
    }
    else if (p -> right != nullptr && p -> left == nullptr){
        temp =p;
        p = temp -> right ;
        delete temp;
    }
    else if (p -> right == nullptr && p -> left != nullptr){
        temp =p;
        p = temp -> left ;
        delete temp;
    }
    else {
        temp = p -> left;
        prev = p;
        while (temp -> right != nullptr){
            prev = temp;
            temp = temp -> right;
        }
        p -> info = temp -> info;
        if(prev == p)
            prev -> left = temp -> left;
        else
            prev -> right = temp -> left;
        delete temp;
    }
}
template <typename  T>
bool Binary_Search_Tree <T>::search(T item) {
    if ( Root == nullptr) {
        cout << "ERROR!\n";
        return false;
    }
    else{
        BTnode<T> *current = Root;
        bool found = false;
        while (current != nullptr && !found) {
            if (current->info == item) {
                found = true;
            } else if (current->info > item) {
                current = current->left;
            } else
            current = current->right;
        }
        return found;
    }
}
