#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <string>   

using namespace std;

int main() {

    // read the records.txt file 
    ifstream ifs;
    ifs.open("records.txt", ifstream::in);

    // check if any issue in reading file
    if (!ifs.good()) {
        cout << "Problem with opening the file" << endl;
        exit(1);
    }
    
    // read the file contents
    string content;
    while (!ifs.eof()) {

        // format is ->
        // number, number
        // description
        
        getline(ifs, content, ',');
        cout << content << endl;

        getline(ifs, content);
        cout << content << endl;

        getline(ifs, content);
        cout << content << endl << endl;
    }

    ifs.close();

    return 0;
}

