// Lyric Moysey-Rubin
// lwm2
// 301614885

#include "a2_question2.h"

// creates a superhero
Superhero *createSuperhero(const char *name, short feetInHeight,
						   short inchesInHeight, const char *superpower,
						   const char *traits) {
	// superhero to be return
	Superhero *superhero = malloc(sizeof(Superhero));

	// null safety
	if (superhero == NULL) {
		return NULL;
	}

	// allocate space for string to make sure it transfers
	superhero->name = malloc(strlen(name) * sizeof(char));
	strcpy(superhero->name, name);
	superhero->feetInHeight = feetInHeight;
	superhero->inchesInHeight = inchesInHeight;
	superhero->superpower = malloc(strlen(superpower) * sizeof(char));
	strcpy(superhero->superpower, superpower);
	superhero->traits = malloc(strlen(traits) * sizeof(char));
	strcpy(superhero->traits, traits);

	return superhero;
}

void clearSuperhero(Superhero *superhero) {
	// null safety check
	if (superhero == NULL) {
		return;
	}
	// free the strings
	free(superhero->traits);
	free(superhero->superpower);
	free(superhero->name);
}
