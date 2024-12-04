// Lyric Moysey-Rubin
// 301614885
// lwm2
#include "a4_superheroList.hpp"
#include "a4_superherolib.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// macros
#define clearInput() \
	cin.clear();     \
	cin.ignore(1024, '\n')

// global variables
SuperheroList *heroes;

// functions
SuperheroList *loadSuperheroesFromFile(const string filename);
void inputLoop();
void opt_loadFile();
void opt_listByHeight();
void opt_listByName();
void opt_lookup();
void opt_add();
void opt_save();

int main(int argc, char *argv[]) {
	cout << "------------------------------------------------------------------"
			"----"
		 << endl
		 << "------------------------ Lyric Moysey-Rubin "
			"--------------------------"
		 << endl
		 << "---------------------------- 301614885 "
			"-------------------------------"
		 << endl
		 << "------------------------------- lwm2 "
			"---------------------------------"
		 << endl;

	// initialize heroes with a value so that you can still preform operations
	// (add hero, save file...) without loading a file
	heroes = new SuperheroList;
	inputLoop();
	cout << "Exiting..." << endl;
	delete heroes;
	heroes = NULL;
	return 0;
}

// Acts as the main loop of the program. Gathers input, and calls whichever
// option is needed for the corresponding input.
void inputLoop() {
	int opt = -1;

	// core of the program. 7 is quit.
	while (opt != 7) {
		cout << "Input a number to choose one of the following options: "
			 << endl
			 << "1) Load a superheroes file" << endl
			 << "2) List superheroes by height" << endl
			 << "3) List superheroes by name" << endl
			 << "4) Look up a superhero" << endl
			 << "5) Add a superhero" << endl
			 << "6) Save a superheroes file" << endl
			 << "7) Quit program" << endl
			 << "Option: ";
		cin >> opt;
		clearInput();
		if (!cin.good()) {
			// avoid some catastophe if the input is invalid
			cout << "Invalid input " << endl;
			opt = -1;
		}
		// when there are heroes, have the full menu be valid.
		if (heroes != NULL && heroes->getSize() > 0) {
			switch (opt) {
			case 1: // load
				opt_loadFile();
				break;
			case 2: // list by height
				opt_listByHeight();
				break;
			case 3: // list by name
				opt_listByName();
				break;
			case 4: // lookup
				opt_lookup();
				break;
			case 5: // add hero
				opt_add();
				break;
			case 6: // save file
				opt_save();
				break;
			case 7: // quit
				return;
				break;
			default:
				cout << "Invalid option: " << opt
					 << " does not correspond to a valid choice. Please "
						"input a different option."
					 << endl;
				break;
			}
		} else { // no heroes to operate on
			switch (opt) {
			case 1: // load
				opt_loadFile();
				break;
			case 5: // add hero
				opt_add();
				break;
			case 7: // quit
				return;
				break;
			default:
				if (opt < 1 || opt > 7) {
					cout << "Invalid option: " << opt
						 << " does not correspond to a valid choice. Please "
							"input a different option."
						 << endl;
				} else {
					cout << "Invalid operation. No heroes are loaded at this "
							"time. Please either load a superheroes file or "
							"insert a hero"
						 << endl;
				}
				break;
			}
		}
		// separate operations for nicer reading
		cout << endl;
	}
}

// open a file
void opt_loadFile() {
	delete heroes;
	string filename;
	cout << "Please enter the name of the file you wish to load: ";
	cin >> filename;
	try {
		heroes = loadSuperheroesFromFile(filename);
	} catch (const char *err) {
		cout << err << endl;
	}
}

// list the heroes by height
void opt_listByHeight() {
	// cout << "LIST BY HEIGHT" << endl;
	heroes->listSuperheroesByHeight();
}

// list the heroes by name
void opt_listByName() {
	// cout << "LIST BY NAME" << endl;
	heroes->listSuperheroesByName();
}

// search for power
void opt_lookup() {
	string searchterm = "";
	cout << "Please enter your superpower search term: ";
	cin >> searchterm;
	clearInput();
	heroes->listSuperheroesContainingSuperpower(searchterm);
}

// add a new hero to the list
void opt_add() {
	string hName = "";
	int hHeightFt = -1;
	int hHeightIn = -1;
	string hPower = "";
	string hDescription = "";
	do {
		cout << "Please input the hero's name: ";
		getline(cin, hName); // handle spaces properly

		// I hate this redundant if statement but I can't figure out how else to
		// alert the user of the input being invalid without also outputting it
		// when it's valid
		if (hName == "" || !cin.good()) {
			clearInput();
			cout << "Invalid input." << endl;
		}
	} while (hName == "" || !cin.good());
	do {
		cout << "Please input the number of feet in the hero's height: ";
		cin >> hHeightFt;

		// See above disclaimer
		if (hHeightFt < 0 || !cin.good()) {
			hHeightFt = -1;
			clearInput();
			cout << "Invalid input." << endl;
		}
		cout << "height feet " << hHeightFt << endl;
	} while (hHeightFt < 0 || !cin.good());
	do {
		cout << "Please input the number of inches in the hero's height: ";
		cin >> hHeightIn;

		// See above disclaimer
		if (hHeightIn < 0 || !cin.good()) {
			hHeightIn = -1;
			clearInput();
			cout << "Invalid input." << endl;
		}
		cout << "height inches " << hHeightIn << endl;
	} while (hHeightIn < 0 || !cin.good());
	clearInput();
	do {
		cout << "Please input the name of the hero's superpower: ";
		getline(cin, hPower);

		// see above disclaimer
		if (hPower == "" || !cin.good()) {
			clearInput();
			cout << "Invalid input." << endl;
		}
	} while (hPower == "" || !cin.good());
	do {
		cout << "Please input the traits of the hero: ";
		getline(cin, hDescription);

		// see above disclaimer
		if (hDescription == "" || !cin.good()) {
			clearInput();
			hDescription = "";
			cout << "Invalid input." << endl;
		}
	} while (hDescription == "" || !cin.good());

	heroes->insertSuperhero(hName, hHeightFt, hHeightIn, hPower, hDescription);
}

// save to a file
void opt_save() {
	string filename;

	cout << "Please insert the name of the file you want to save (WARNING: "
			"WILL OVERWRITE EXISTING FILES): ";
	getline(cin, filename);
	try {
		heroes->saveSuperheroesToFile(filename);
		cout << "Save hero data to " << filename << endl;
	} catch (const char *err) {
		cout << err << endl;
	}
}

// load from a file
SuperheroList *loadSuperheroesFromFile(const string filename) {
	ifstream file;
	string line;

	file.open(filename);

	if (!file.is_open()) {
		throw "Err: Could not open file. Check if it exists?";
	}

	SuperheroList *heroList = new SuperheroList;

	string hName = "";
	int hHeightFt = 0;
	int hHeightIn = 0;
	string hPower = "";
	string hDescription = "";
	while (getline(file, line)) {
		// cout << line << endl;

		if (line.length() > 0) {
			if (line[0] == '*') {
				// +1 is to make sure the space *isn't* included
				int splitAt = line.find_first_of(" ") + 1;

				switch (splitAt) {
				case 10: // Name
					hName = line.substr(splitAt);
					break;
				case 12: // Height
				{		 // gotta protect the scope
					int heightSplitAt = line.find_first_of('\'');
					hHeightFt =
						stoi(line.substr(splitAt, heightSplitAt - splitAt));
					hHeightIn = stoi(line.substr(heightSplitAt + 1));
				} break;
				case 16: // Superpower
					hPower = line.substr(splitAt);
					break;
				}

			} else {
				hDescription = line;
			}
		}
		if (hName.length() > 0 && hDescription.length() > 0) {
			heroList->insertSuperhero(hName, hHeightFt, hHeightIn, hPower,
									  hDescription);
			hName = "";
			hHeightFt = 0;
			hHeightIn = 0;
			hPower = "";
			hDescription = "";
		}
	}

	return heroList;
}
