#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
/**________________________________________________________________**/
/** Division hashing function **/
int division(int key,int size){
    return key%size;
}
/**________________________________________________________________**/
/** Multiplication hashing function using constant A **/
int multiplication(int key,int size){
    double a= 0.618033; // constant
    double res = key * a;
    double fraction_res = res- floor(res); // Extract fractional part
    return static_cast<int>(floor(size*fraction_res));
}
/**________________________________________________________________**/
/** Mid-square hashing function **/
int mid_square(int key,int size){
    long long res = key * key; // Square the key
    string  squared= to_string(res);
    string k;
    int n = squared.size(),r = static_cast<int>(log10(size))+1,middle=(n-r)/2; // get r digits and middle
    k = squared.substr(middle,r); // Extract middle r digits
    int final = stoi(k);
    return final%size;
}
/**________________________________________________________________**/
/** Folding hashing function **/
int folding(long long key,int size,int space){
    string res = to_string(key),temp;
    vector<string> k;
    // Split key into parts of 'space' length
    for(int i=0;i<res.size();++i){
        // append character in temp then check if temp size reached space
        temp.push_back(res[i]);
        if(temp.size()==space){
            k.push_back(temp);
            temp.clear();
        }
    }
    // if temp.size()<space
    if (!temp.empty()) {
        k.push_back(temp);
    }
    int sum=0;
    // Convert parts to integers and sum them
    for(string i:k)
        sum+= stoi(i);
    return sum%size;
}
/**________________________________________________________________**/
/** Bound folding hashing function **/
int bound_folding(long long key,int size,int space){
    string res = to_string(key),temp;
    vector<string> k;
    // Split key into parts of 'space' length
    for(int i=0;i<res.size();++i){
        // append character in temp then check if temp size reached space
        temp.push_back(res[i]);
        if(temp.size()==space){
            k.push_back(temp);
            temp.clear();
        }
    }
    // if temp.size()<space
    if (!temp.empty()) {
        k.push_back(temp);
    }
    // Reverse the first and last parts if 21 it will be 12
    if (!k.empty()) {
        reverse(k.front().begin(), k.front().end());
        reverse(k.back().begin(), k.back().end());
    }
    long long sum=0;
    // Convert parts to integers and sum them
    for(string i:k)
        sum+= stoll(i);
    return sum%size;
}
/**________________________________________________________________**/
/** Separate Chain hashing class **/
class chain{
    int threshold=2,size,number;
    vector<list<int>>table; // Hash table with linked lists for chaining
public:
    chain(){
        number=0; // Initialize number of elements
        size=3; // Initial table size
        table.resize(size);
    }
    /** Calculate load factor **/
    int load_factor() {
        int k;
        if(number%size)
            k= (number / size)+1;
        else
            k= number/size;
        return k+1;
    }
    /** Rehash to a new larger table **/
    void rehash(){
        int new_size=size*2; // Double the table size
        vector<list<int>>new_table(new_size);
        // Rehash existing elements
        for(int i=0;i<size;++i)
            for(int val:table[i])
                new_table[division(val,new_size)].push_back(val);
        table=new_table;
        size=new_size;
    }
    /** Insert a key into the table **/
    void insert(int key){
        if(load_factor()> threshold) // Rehash if load factor exceeds threshold
            rehash();
        table[division(key,size)].push_back(key);
        number ++;
    }
    /** Delete a key from the table **/
    void delete_(int key) {
        if (search(key)) { // search for key first
            table[division(key, size)].remove(key); // Remove the key from the list
            number--;
        }
        else
            cout<<"not found\n";
    }
    /** Search for a key in the table **/
    bool search(int key){
        int index = division(key,size);
        // search for key in the linked list index
        for(int val : table[index])
            if(val == key)
                return true;
        return false;
    }
    /** Print the hash table **/
    void print(){
        for(int i=0;i<size ;++i){
            cout<<"Keys in Linked List "<<i<<'\n';
            for(int key:table[i])
                cout << key << ' ';
            cout<<"\n";
        }
        cout<<"------------------------------------\n";
    }
};
/**________________________________________________________________**/
/** Open addressing hashing class **/
class open_addressing{
private:
    int size,number,prime;
    float threshold=0.75; // Load factor will be compared with threshold
    char way; // Collision resolution method (probing)
    vector<int>normal; // Store inserted keys for rehashing
    vector<pair<char, int>>table; // Hash table ('e' = empty, 'd' = deleted, 'i' = inserted)
    /** Check if a number is prime **/
    bool is_prim(int prim){
        // if even false
        if(prim<=1 || !(prim%2))
            return false;
        if(prim==2)
            return true;
        // take sqrt(prim) as complexity (increase efficiency)
        for(int i=3;i<=sqrt(prim);i+=2)
            if(!(prim%i))
                return false;
        return true;
    }
    /** Initialize the hash table **/
    void initialize(vector<pair<char,int>>&v){
        for(int i=0;i<v.size();++i)
            v[i].first='e',v[i].second=-1;// make it empty 'e'
    }
public:
    open_addressing(int length , char c='h') : table(length){
        size=length;
        number=0;
        prime=size-1;
        if(c == 'h' || c== 'l' || c=='q')
            way = c; // 'h' = double hashing, 'l' = linear probing, 'q' = quadratic probing
        else
            cout<<"you have enter wrong character so it will be double hashing\n";
        // get prime number just smaller than size
        while(prime>1){
            if(is_prim(prime)){
                break;
            }
            prime--;
        }
        initialize(table);
    }
    /** Linear probing formula **/
    int linear(int key,int i){
        return division(key+i,size);
    }
    /** Quadratic probing formula **/
    int quadratic(int key,int i){
        return division(key+(i*i),size);
    }
    /** Secondary hash function for double hashing **/
    int hash2(int key){
        return prime+(key%prime);
    }
    /** Double hashing formula **/
    int double_hashing(int key,int i){
        return division(division(key,size)+(i*hash2(key)),size);
    }
    /** Insert a key using the chosen collision resolution method **/
    void insert(int key){
        bool inserted=false;
        if(load_factor()>threshold) // Rehash if load factor exceeds threshold
            rehash();
        if(way=='l') { // Linear probing
            for (int i = 0; i < size && !inserted; ++i) {
                int index = linear(key,i);
                if(table[index].first!='i') { // insert in 'e' or 'd' only
                    table[index].second = key;
                    table[index].first='i'; // mark as inserted
                    inserted=true;
                    normal.push_back(key); // insert in normal to simplify rehash
                }
            }
        }
        else if(way == 'q'){ // Quadratic probing
            for (int i = 0; i < size && !inserted; ++i) {
                int index = quadratic(key,i);
                if(table[index].first!='i') { // insert in 'e' or 'd' only
                    table[index].second = key;
                    table[index].first='i';
                    inserted=true;
                    normal.push_back(key); // insert in normal to simplify rehash
                }
            }
        }
        else if(way=='h'){ // Double hashing
            for (int i = 0; i < size && !inserted; ++i) {
                int index = double_hashing(key,i);
                if(table[index].first!='i') { // insert in 'e' or 'd' only
                    table[index].second = key;
                    table[index].first='i'; // mark as inserted
                    inserted=true;
                    normal.push_back(key); // insert in normal to simplify rehash
                }
            }
        }
        if(!inserted)
            cout<<"failed to insert!\n";
        else
            number++;
    }
    /** Delete a key using the chosen collision resolution method **/
    void delete_(int key){
        bool deleted=false;
        if(search(key)) {
            if (way == 'l') { // Linear probing
                for (int i = 0; i < size && !deleted; ++i) {
                    int index = linear(key, i);
                    if (table[index].second == key) { // if key found in that index
                        table[index].second = -1;
                        table[index].first = 'd'; // mark it as deleted to make search works efficiently
                        deleted = true;
                        auto it = find(normal.begin(), normal.end(), key);
                        normal.erase(it); // delete it from normal too
                    }
                }
            } else if (way == 'q') { // Quadratic probing
                for (int i = 0; i < size && !deleted; ++i) {
                    int index = quadratic(key, i);
                    if (table[index].second == key) { // if key found in that index
                        table[index].second = -1;
                        table[index].first = 'd'; // mark it as deleted to make search works efficiently
                        deleted = true;
                        auto it = find(normal.begin(), normal.end(), key);
                        normal.erase(it); // delete it from normal too
                    }
                }
            } else if (way == 'h') { // Double hashing
                for (int i = 0; i < size && !deleted; ++i) {
                    int index = double_hashing(key, i);
                    if (table[index].second == key) { // if key found in that index
                        table[index].second = -1;
                        table[index].first = 'd'; // mark it as deleted to make search works efficiently
                        deleted = true;
                        auto it = find(normal.begin(), normal.end(), key);
                        normal.erase(it); // delete it from normal too
                    }
                }
            }
        }
        if(!deleted)
            cout<<"failed to delete!\n";
        else
            number--;
    }
    /** Search for a key using the chosen collision resolution method **/
    bool search(int key){
        bool found=false;
        if(way=='l') { // Linear probing
            for (int i = 0; i < size && !found; ++i) {
                int index = linear(key,i);
                if(table[index].first=='i' && table[index].second==key)
                    found=true;
                else if(table[index].first=='e'){ // stop searching if e found
                    found = false;
                    break;
                }
            }
        }
        else if(way == 'q'){ // Quadratic probing
            for (int i = 0; i < size && !found; ++i) {
                int index = quadratic(key,i);
                if(table[index].first=='i' && table[index].second==key)
                    found=true;
                else if(table[index].first=='e'){ // stop searching if e found
                    found = false;
                    break;
                }
            }
        }
        else if(way=='h'){ // Double hashing
            for (int i = 0; i < size && !found; ++i) {
                int index = double_hashing(key,i);
                if(table[index].first=='i' && table[index].second==key)
                    found=true;
                else if(table[index].first=='e'){ // stop searching if e found
                    found = false;
                    break;
                }
            }
        }
        return found;
    }
    /** Print the hash table **/
    void print(){
        for(int i=0;i<size;++i)
            if(table[i].first=='i')
                cout<<"item in index "<<i<<" : "<<table[i].second<<'\n';
            else
                cout<<"empty index "<<i<<"\n";
    }
    /** Calculate the current load factor **/
    float load_factor() {
        return float((number+1))/size;
    }
    /** Rehash to a new larger table **/
    void rehash(){
        int new_size=size*2; // Double the table size
        vector<pair<char,int>>new_table(new_size);
        initialize(new_table);
        size=new_size; // update size
        prime=size; // update prime
        while(prime>1){
            if(is_prim(prime)){
                break;
            }
            prime--;
        }
        if(way=='l') { // Rehash using linear probing
            // loop on items in the normal
            for (int i = 0; i < normal.size(); ++i) {
                for(int j=0;j<new_size;++j){
                    // found index according ro new prime and size
                    int index = linear(normal[i],j);
                    if(new_table[index].first!='i') {
                        new_table[index].second = normal[i];
                        new_table[index].first='i';
                        break;
                    }
                }
            }
        }
        else if(way =='q'){ // Rehash using quadratic probing
            // loop on items in the normal
            for (int i = 0; i < normal.size(); ++i) {
                for(int j=0;j<new_size;++j){
                    // found index according ro new prime and size
                    int index = quadratic(normal[i],j);
                    if(new_table[index].first!='i') {
                        new_table[index].second = normal[i];
                        new_table[index].first='i';
                        break;
                    }
                }
            }
        }
        else if(way=='h'){ // Rehash using double hashing
            // loop on items in the normal
            for (int i = 0; i < normal.size(); ++i) {
                for (int j = 0; j < new_size; ++j) {
                    // found index according ro new prime and size
                    int index = double_hashing(normal[i], j);
                    if (new_table[index].first != 'i') {
                        new_table[index].second = normal[i];
                        new_table[index].first = 'i';
                        break;
                    }
                }
            }
        }
        table=new_table;
    }
};
/**________________________________________________________________**/
/** Menu **/
void menu(){
    cout << "\n=========================\n";
    cout << " Hash Table Operations\n";
    cout << "=========================\n";
    cout << "1. Insert into Separate Chain Hash Table\n";
    cout << "2. Delete from Separate Chain Hash Table\n";
    cout << "3. Search in Separate Chain Hash Table\n";
    cout << "4. Print Separate Chain Hash Table\n";
    cout << "-------------------------\n";
    cout << "5. Insert into Open Addressing Hash Table\n";
    cout << "6. Delete from Open Addressing Hash Table\n";
    cout << "7. Search in Open Addressing Hash Table\n";
    cout << "8. Print Open Addressing Hash Table\n";
    cout << "=========================\n";
    cout << " Hash Functions Menu\n";
    cout << "=========================\n";
    cout << "9. Division Hashing\n";
    cout << "10. Multiplication Hashing\n";
    cout << "11. Mid Square Hashing\n";
    cout << "12. Folding Hashing\n";
    cout << "13. Bound Folding Hashing\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}
/**________________________________________________________________**/
/** Main **/
int main() {
    char choices;
    int sizes;
    chain chain_table;
    cout<<"choose probing way: l(linear),q(quadratic),h(double hashing)";
    cin>>choices;
    cout<<"choose beginning size for open addressing: ";
    cin>>sizes;
    open_addressing open_table(sizes, choices);
    while (true) {
        menu();
        int choice;
        cin >> choice;
        if (cin.fail()) { // Input validation
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: {
                int key;
                cout << "Enter key to insert into Separate Chain Hash Table: ";
                cin >> key;
                chain_table.insert(key);
                break;
            }
            case 2: {
                int key;
                cout << "Enter key to delete from Separate Chain Hash Table: ";
                cin >> key;
                chain_table.delete_(key);
                break;
            }
            case 3: {
                int key;
                cout << "Enter key to search in Separate Chain Hash Table: ";
                cin >> key;
                if (chain_table.search(key))
                    cout << "Key found in Separate Chain Hash Table.\n";
                else
                    cout << "Key not found in Separate Chain Hash Table.\n";
                break;
            }
            case 4:
                chain_table.print();
                break;
            case 5: {
                int key;
                cout << "Enter key to insert into Open Addressing Hash Table: ";
                cin >> key;
                open_table.insert(key);
                break;
            }
            case 6: {
                int key;
                cout << "Enter key to delete from Open Addressing Hash Table: ";
                cin >> key;
                open_table.delete_(key);
                break;
            }
            case 7: {
                int key;
                cout << "Enter key to search in Open Addressing Hash Table: ";
                cin >> key;
                if (open_table.search(key))
                    cout << "Key found in Open Addressing Hash Table.\n";
                else
                    cout << "Key not found in Open Addressing Hash Table.\n";
                break;
            }
            case 8:
                open_table.print();
                break;
            case 0:
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            case 9: {
                int key,size;
                cout << "Enter key and table size: ";
                cin >> key >> size;
                cout << "Hash value (Division): " << division(key, size) << "\n";
                break;
            }
            case 10: {
                int key,size;
                cout << "Enter key and table size: ";
                cin >> key >> size;
                cout << "Hash value (Multiplication): " << multiplication(key, size) << "\n";
                break;
            }
            case 11: {
                int key,size;
                cout << "Enter key and table size: ";
                cin >> key >> size;
                cout << "Hash value (Mid Square): " << mid_square(key, size) << "\n";
                break;
            }
            case 12: {
                long long key;
                int size,space;
                cout << "Enter key, table size, and space: ";
                cin >> key >> size >> space;
                cout << "Hash value (Folding): " << folding(key, size, space) << "\n";
                break;
            }
            case 13: {
                long long key;
                int size,space;
                cout << "Enter key, table size, and space: ";
                cin >> key >> size >> space;
                cout << "Hash value (Bound Folding): " << bound_folding(key, size, space) << "\n";
                break;
            }
            default:
                cout << "Invalid choice. Please select a valid option.\n";
        }
    }
}
