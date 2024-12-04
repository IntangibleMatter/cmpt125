// Lyric Moysey-Rubin
// 301614885
// lwm2
#include "a4_superheroList.hpp"
#include "a4_superherolib.hpp"
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

SuperheroList::SuperheroList() {}

SuperheroList::~SuperheroList() {
	for (auto hero = this->superheroEntries.begin();
		 hero != this->superheroEntries.end(); hero++) {
		delete (*hero);
	}
	cout << this->getSize();
	this->superheroEntries.clear();
}

int SuperheroList::getSize() { return this->superheroEntries.size(); }

void SuperheroList::listSuperheroesByHeight() {
	if (!this->superheroEntries.empty()) {
		stable_sort(this->superheroEntries.begin(),
					this->superheroEntries.end(), compareSuperheroesByHeight);
	}
	for (auto hero = this->superheroEntries.begin();
		 hero != this->superheroEntries.end(); hero++) {
		if ((*hero) != NULL) {
			cout << "~~~HERO~~~" << endl;
			cout << "Name:   " << (*hero)->name << endl;
			cout << "Height: " << (*hero)->feetInHeight << "ft "
				 << (*hero)->inchesInHeight << "in" << endl;
			cout << "Power:  " << (*hero)->superpower << endl;
			cout << "Desc:   " << (*hero)->traits << endl;
		}
	}
}

void SuperheroList::listSuperheroesByName() {
	if (!this->superheroEntries.empty()) {
		stable_sort(this->superheroEntries.begin(),
					this->superheroEntries.end(), compareSuperheroesByName);
	}
	for (auto hero = this->superheroEntries.begin();
		 hero != this->superheroEntries.end(); hero++) {
		if ((*hero) != NULL) {
			cout << "~~~HERO~~~" << endl;
			cout << "Name:   " << (*hero)->name << endl;
			cout << "Height: " << (*hero)->feetInHeight << "ft "
				 << (*hero)->inchesInHeight << "in" << endl;
			cout << "Power:  " << (*hero)->superpower << endl;
			cout << "Desc:   " << (*hero)->traits << endl;
		}
	}
}

void SuperheroList::insertSuperhero(const string name, short feetInHeight,
									short inchesInHeight,
									const string superpower,
									const string traits) {
	this->superheroEntries.push_back(createSuperhero(
		name, feetInHeight, inchesInHeight, superpower, traits));
}

void SuperheroList::listSuperheroesContainingSuperpower(
	const string keySuperpower) {
	bool foundHero = false;
	for (auto hero = this->superheroEntries.begin();
		 hero != this->superheroEntries.end(); hero++) {
		if ((*hero)->superpower.find(keySuperpower) != string::npos) {
			foundHero = true;
			cout << "~~~HERO~~~" << endl;
			cout << "Name:   " << (*hero)->name << endl;
			cout << "Height: " << (*hero)->feetInHeight << "ft "
				 << (*hero)->inchesInHeight << "in" << endl;
			cout << "Power:  " << (*hero)->superpower << endl;
			cout << "Desc:   " << (*hero)->traits << endl;
		}
	}
	if (!foundHero) {
		cout << "No such superhero on record." << endl;
	}
}

void SuperheroList::saveSuperheroesToFile(const string filename) {
	ofstream file;
	file.open(filename);

	if (!file.is_open()) {
		throw "Err: Could not open file to write to";
	}

	for (auto hero = this->superheroEntries.begin();
		 hero != this->superheroEntries.end(); hero++) {
		file << "**Name:** " << (*hero)->name << endl;
		file << "**Height:** " << (*hero)->feetInHeight << '\''
			 << (*hero)->inchesInHeight << '"' << endl;
		file << "**Superpower:** " << (*hero)->superpower << endl;
		file << (*hero)->traits << endl;
		file << endl;
	}
}
