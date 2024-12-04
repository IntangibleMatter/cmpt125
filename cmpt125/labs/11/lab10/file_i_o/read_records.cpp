#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <string>   

using namespace std;
int main(){


    int myInt;

    string myStr;

    cout << "Enter an integer: ";

    cin >> myInt;

    cout << "Enter a string: ";

    getline(cin, myStr);


    cout << "You have entered " << myInt << " and " << myStr << endl;

    int myInt2;

    string myStr2;

    cout << "Enter an integer: ";

    cin >> myInt2;

    cout << "Enter a string: ";

    getline(cin >> ws, myStr2);


    cout << "You have entered " << myInt2 << " and " << myStr2 << endl;


    return 0;   
}   

