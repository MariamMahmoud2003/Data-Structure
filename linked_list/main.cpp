#include <iostream>
#include "implementation.h"
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;
string getSize(string s){
    ifstream in (s);
    string line;
    getline(in , line);
    in.ignore();
    return line;
}
void readFromFile(string fileName , SIngleLinkedList* ob){
    ifstream in (fileName);//open file
    string line;
    int count = 0 , i = 0 , start = 0;
    while(getline(in,line)) {//fill array with values in our file
        if (count == 1 and start != 0) {
            ob[i].setName(line);
        }
        else if (count == 2) {
            ob[i].setId(stoi(line));
        } else if (count == 3) {
            ob[i].setGpa(stod(line));
        }
        if(count % 3 == 0 and count != 0){
            count = 0;
            i++;
        }
        if(start == 0) {
            start++;
        }
        count++;
    }
}
void BubbleSortByName(SIngleLinkedList* ob , int size){
    ofstream out; //for printing in file
    out.open("out");
    out << "Bubble Sort\n";
    out << "___________\n";
    out << "Number of comparison is n^2 " << size * size << "\n";
    out << "______________________________\n";
    // begin of program
    auto start = high_resolution_clock::now();
    bool flag = true;
    for (int i = 0; i < size - 1 && flag; ++i) {
        flag = false;
        for (int k = size - 1; k > 0; --k) {
            if (ob[k] > ob[k - 1]) {
                swap(ob[k], ob[k - 1]);
                flag = true;
            }
        }
    }
    auto stop = high_resolution_clock::now();
    // measure duration in microsecond
    auto duration = duration_cast<microseconds>(stop - start);
    out << "Time taken by function: " << duration.count() << " microseconds" << endl;
    out << "_________________________________________\n";
    for(int i = 0 ; i < size ; ++i){
        out << ob[i].print() << endl;
        out << "________\n";
    }
    out.close();
}
void BubbleSortByGPA(SIngleLinkedList* ob , int size){
    ofstream out; //for printing in file
    out.open("out");
    out << "Bubble Sort\n";
    out << "___________\n";
    out << "Number of comparison is n^2 " << size * size << "\n";
    out << "______________________________\n";
    // begin of program
    auto start = high_resolution_clock::now();
    bool flag = true;
    for (int i = 0; i < size - 1 && flag; ++i) {
        flag = false;
        for (int k = size - 1; k > 0; --k) {
            if (ob[k] < ob[k - 1]) {
                swap(ob[k], ob[k - 1]);
                flag = true;
            }
        }
    }
    auto stop = high_resolution_clock::now();
    // measure duration in microsecond
    auto duration = duration_cast<microseconds>(stop - start);
    out << "Time taken by function: " << duration.count() << " microseconds" << endl;
    out << "_________________________________________\n";
    for(int i = 0 ; i < size ; ++i){
        out << ob[i].print() << endl;
        out << "________\n";
    }
    out.close();
}
int main() {
    string fileName;
    cout << "Enter File Name\n";
    cin >> fileName;
    int n = stoi(getSize(fileName));
    SIngleLinkedList ob[n];
    readFromFile(fileName, ob);
    int no, choose;
    cout << "Choose sorting algorithm\n1)Bubble\n";
    cin >> choose;
    cout << "1:SortByGpa || 2:SortByName\n";
    cin >> no;
    if (choose == 1) {
        if (no == 1) {
            BubbleSortByGPA(ob, n);
        } else {
            BubbleSortByName(ob, n);
        }
    }
    return 0;
}
    /*int count = 1,j = 0,size,choose;
    string filename = "input";
    ifstream in (filename);//open file
    if(!(in>>size)){
        cout<<"error";
        return 1 ;
    }
    in.ignore();
    SIngleLinkedList ob[size];
    string line;
    // begin of program
    cout<<"Please enter how to sort\n1)By GPA\n2)By Name\n";
    cin>>choose;
    if(choose==1) {
        auto start = high_resolution_clock::now();
        while (getline(in, line)) {
            if (count == 1)
                ob[j].setName(line);
            else if (count == 2)
                ob[j].setId(line);
            else if (count == 3)
                ob[j].setGpa(std::stod(line));
            count++;
            if (count > 3) {
                count = 1;
                j++;
            }
        }
        bool flag = true;
        for (int i = 0; i < size - 1 && flag; ++i) {
            flag = false;
            for (int k = size - 1; k > 0; --k) {
                if (ob[k] < ob[k - 1]) {
                    swap(ob[k], ob[k - 1]);
                    flag = true;
                }
            }
        }
        ofstream out;
        out.open("out");
        out << "Bubble Sort\n";
        out << "___________\n";
        for (int i = 0; i < size; ++i) {
            out << ob[i].print() << endl;
            out << "________\n";
        }
        // end of program
        auto stop = high_resolution_clock::now();
        // measure duration in microsecond
        auto duration = duration_cast<microseconds>(stop - start);
        out << "Time taken by function: " << duration.count() << " microseconds" << endl;
        out << "_________________________________________\n";
        out << "Number of comparison is n^2 " << size * size << "\n";
        out << "______________________________\n";
        out.close();
    }
    else if (choose==2){
        auto start = high_resolution_clock::now();
        while (getline(in, line)) {
            if (count == 1)
                ob[j].setName(line);
            else if (count == 2)
                ob[j].setId(line);
            else if (count == 3)
                ob[j].setGpa(std::stod(line));
            count++;
            if (count > 3) {
                count = 1;
                j++;
            }
        }
        bool flag = true;
        for (int i = 0; i < size - 1 && flag; ++i) {
            flag = false;
            for (int k = size - 1; k > 0; --k) {
                if (ob[k] > ob[k - 1]) {
                    swap(ob[k], ob[k - 1]);
                    flag = true;
                }
            }
        }
        ofstream out;
        out.open("out");
        out << "Bubble Sort\n";
        out << "___________\n";
        for (int i = 0; i < size; ++i) {
            out << ob[i].print() << endl;
            out << "________\n";
        }
        // end of program
        auto stop = high_resolution_clock::now();
        // measure duration in microsecond
        auto duration = duration_cast<microseconds>(stop - start);
        out << "Time taken by function: " << duration.count() << " microseconds" << endl;
        out << "_________________________________________\n";
        out << "Number of comparison is n^2 " << size * size << "\n";
        out << "______________________________\n";
        out.close();
    }
    else{
        cout<<"Error\n";
    }
    return 0;}*/