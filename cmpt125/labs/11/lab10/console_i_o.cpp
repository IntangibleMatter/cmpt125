#include <cstring> //using the legacy library for Cstring
#include <iostream>
#include <string>
using namespace std;
// test

// same code can be placed in main, putting it here for organizing
void cinDemo() {
	cout << "Input an integer, a character, ";
	cout << "and a float (press enter after each):\n";
	// this reads input from stdin and automatically uses the appropriate format
	int number1;
	char character;
	float number2;
	cin >> number1 >> character >> number2;

	// this writes the value to stdout and automatically formats it
	cout << "The first number is: " << number1 << endl;
	cout << "The character is: " << character << endl;
	cout << "The second number is: " << number2 << endl;
}

// same code can be placed in main, putting it here for organizing
void getlineDemo() {
	cout << "Input something and press enter:\n";
	// cin >> char[] reads a character sequence and makes it into a Cstring
	// cin.getline reads in a character sequence till \n or
	//  the max number -1 is read and makes it into a Cstring
	char userInput[128];
	cin.getline(userInput, 128); // try cin >> userInput

	cout << "You have entered:\n";
	cout << userInput << endl;
	cout << "length is " << strlen(userInput) << endl;
}

// same code can be placed in main, putting it here for organizing
void getlineWithStringDemo() {
	cout << "Input something and press enter:\n";
	// cin doesn't support reading string, use getline(cin, string)
	string userInputStr;
	getline(cin, userInputStr);

	cout << "You have entered:\n";
	cout << userInputStr << endl;
	// note the member method length() is used to get the length
	cout << "length is " << userInputStr.length() << endl;
}

// same code can be placed in main, putting it here for organizing
void coutFormattingDemo() {
	double myPi = 3.14159265359;
	cout.setf(ios::fixed); // this makes the precision work only oo the decimals
	cout.precision();
	cout << "myPi with default precision: " << myPi << endl;
	cout.precision(2);
	cout << "myPi with default precision=2: " << myPi << endl;
	cout.precision(4);
	cout << "myPi with default precision=4: " << myPi << endl;
	// try precision more than the number of decimals, what will happen?
}

int main() {
	// comment out any of the following to try just one demo
	// cinDemo();
	// getlineDemo(); //if this is called right after cinDemo, it'll end itself,
	// why? getlineWithStringDemo();

	// coutFormattingDemo();

	return 0;
}
