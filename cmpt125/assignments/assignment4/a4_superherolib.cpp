// Lyric Moysey-Rubin
// 301614885
// lwm2
#include "a4_superherolib.hpp"
#include <iostream>

using namespace std;

Superhero *createSuperhero(const string name, short feetInHeight,
						   short inchesInHeight, const string superpower,
						   const string traits) {
	Superhero *nhero = new Superhero;
	nhero->name = name;
	nhero->feetInHeight = feetInHeight;
	nhero->inchesInHeight = inchesInHeight;
	nhero->superpower = superpower;
	nhero->traits = traits;
	return nhero;
}

void printSuperhero(const Superhero *pSuperhero) {
	cout << pSuperhero->name << endl
		 << pSuperhero->feetInHeight << "'" << pSuperhero->inchesInHeight
		 << "\"" << endl
		 << pSuperhero->superpower << ": " << pSuperhero->traits << endl;
}

bool compareSuperheroesByHeight(const Superhero *p1, const Superhero *p2) {
	int h1 = p1->feetInHeight * 12 + p1->inchesInHeight;
	int h2 = p2->feetInHeight * 12 + p2->inchesInHeight;
	if (h1 == h2) {
		return compareSuperheroesByName(p1, p2);
	}
	return h1 < h2;
}

bool compareSuperheroesByName(const Superhero *p1, const Superhero *p2) {
	if (p1->name == p2->name) {
		return p1->feetInHeight * 12 + p1->inchesInHeight <
			   p2->feetInHeight * 12 + p2->inchesInHeight;
	}
	return p1->name < p2->name;
}
