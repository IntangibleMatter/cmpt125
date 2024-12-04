#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm> //has the sort function demo-ed here
#include <string>
using namespace std;

//a very simple struct, can also be a class
typedef struct {
    string name;
    int id;
} Person;

//The value returned indicates whether the element passed as first argument
// is considered to go before the second, true if yes, false otherwise
bool comparePersonById(Person p1, Person p2) {
    return p1.id < p2.id;
}

int main() {
    
    Person p1 = { .name = "Alice", .id = 2 };
    Person p2 = { .name = "Bob", .id = 1 };
    Person p3 = { .name = "Charlie", .id = 4 };
    Person p4 = { .name = "Danny", .id = 3 };
    
    //a queue
    queue<Person> pQueue;
    pQueue.push(p1);
    pQueue.push(p2);
    pQueue.push(p3);
    pQueue.push(p4);
    
    cout << "content in pQueue" << endl;
    while(!pQueue.empty()) {
        cout << "name is " << pQueue.front().name
            << " and id is " << pQueue.front().id
            << endl;
        pQueue.pop(); //removes the oldest (FIFO)
    }
    
    //a stack
    stack<Person> pStack;
    pStack.push(p1);
    pStack.push(p2);
    pStack.push(p3);
    pStack.push(p4);
    
    cout << "content in pStack" << endl;
    while(!pStack.empty()) {
        cout << "name is " << pStack.top().name
            << " and id is " << pStack.top().id
            << endl;
        pStack.pop(); //removes the latest (LIFO)
    }
    
    //a vector
    vector<Person> pVector;
    pVector.push_back(p1);
    pVector.push_back(p2);
    pVector.push_back(p3);
    pVector.push_back(p4);
    
    cout << "content in pVector" << endl;
    for (int i=0; i<pVector.size(); i++) {
        cout << "name is " << pVector[i].name
            << " and id is " << pVector[i].id
            << endl;
    }
    
    //do a sort by id, using iterator and function pointer
    sort(pVector.begin(), pVector.end(), comparePersonById);
    
    cout << "content in pVector after sort by id" << endl;
    for (vector<Person>::iterator itr=pVector.begin();
            itr!=pVector.end(); itr++) {
        //iterator is a pointer-like object so dereference it
         cout << "name is " << itr->name
            << " and id is " << itr->id
            << endl;       
    }

    return 0;
}
