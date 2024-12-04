// Lyric Moysey-Rubin
// 301614885
// lwm2@sfu.ca
#include "a3_superherolib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assigns all the variables and mallocs a new hero for use.
Superhero *createSuperhero(const char *name, short feetInHeight,
						   short inchesInHeight, const char *superpower,
						   const char *traits) {
	Superhero *newHero = malloc(sizeof(Superhero));
	// printf("Malloced %i bytes at newHero\n", (int)sizeof(Superhero));
	/*printf("Creating hero with name %s, height %i'%i\", superpower %s, and "
		   "traits %s\n",
		   name, feetInHeight, inchesInHeight, superpower, traits);*/

	newHero->name = malloc((strlen(name) + 1) * sizeof(char));
	newHero->superpower = malloc((strlen(superpower) + 1) * sizeof(char));
	newHero->traits = malloc((strlen(traits) + 1) * sizeof(char));
	strcpy(newHero->name, name);
	newHero->feetInHeight = feetInHeight;
	newHero->inchesInHeight = inchesInHeight;
	strcpy(newHero->superpower, superpower);
	strcpy(newHero->traits, traits);

	return newHero;
}

// frees all the strings malloced with a hero
void clearSuperhero(Superhero *superhero) {
	if (superhero == NULL) {
		return;
	}
	free(superhero->name);
	free(superhero->superpower);
	free(superhero->traits);
}

// wrapper for clearSuperhero, freeing the superhero struct too.
void removeSuperhero(Superhero *superhero) {
	if (superhero == NULL) {
		return;
	}
	clearSuperhero(superhero);
	free(superhero);
	superhero = NULL;
}

// Don't know what I can say, does what it says on the tin.
Superhero **lookupSuperheroBySuperpower(Superhero **array, int size,
										const char *superpower) {
	int heroCount = 1; // An extra +1 for the NULL at the end
	Superhero **foundHeroes = malloc(sizeof(Superhero *) * heroCount);

	for (int i = 0; i < size; i++) {
		if (substringExists(array[i]->superpower, superpower)) {
			foundHeroes[heroCount - 1] = array[i];
			// ordered like this so that the NULL gets added to the end
			heroCount++;
			foundHeroes = realloc(foundHeroes, sizeof(Superhero *) * heroCount);
		}
	}

	foundHeroes[heroCount - 1] = NULL;

	return foundHeroes;
}

// simple comparison function, with an strcmp so that if two heroes have the
// same name and height the two compares don't recurse forever.
int compareSuperheroesByHeight(const void *p1, const void *p2) {
	int h1 = getHeroHeight(*((Superhero **)(p1)));
	int h2 = getHeroHeight(*((Superhero **)(p2)));

	if (h1 < h2) {
		return -1;
	} else if (h1 == h2) {
		// avoid infinte recursion
		return strcmp((*((Superhero **)(p1)))->name,
					  (*((Superhero **)(p2)))->name);

	} else {
		return 1;
	}
}

// you get one guess what it does. Like above, used for quicksort.
int compareSuperheroesByName(const void *p1, const void *p2) {
	int cmp = strcmp((*((Superhero **)p1))->name, (*((Superhero **)p2))->name);

	if (cmp == 0) {
		// this is set up as a safety so that if name and height are the same
		// we don't get an infinite recursion
		if (getHeroHeight(p1) - getHeroHeight(p2) == 0) {
			return 0;
		} else {
			return compareSuperheroesByHeight(p1, p2);
		}
	} else {
		return cmp;
	}
}

// wrapper for qsort() so that you don't need as much boilerplate.
void sortSuperheros(Superhero **array,
					int (*compar)(const void *, const void *)) {
	qsort(array, getHeroArraySize(array), sizeof(Superhero *), compar);
}

// gets a hero's height
int getHeroHeight(const Superhero *hero) {
	return hero->feetInHeight * 12 + hero->inchesInHeight;
}

// checks to see if a substring exists in a string.
bool substringExists(const char *string, const char *substring) {
	return (strstr(string, substring) != NULL);
}

// gets the size of the array of superheroes
int getHeroArraySize(Superhero **array) {
	int size = 0;
	while (array[size] != NULL) {
		size++;
	}
	return size;
}
