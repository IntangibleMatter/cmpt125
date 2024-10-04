#include "a2_question2.h"

Superhero *createSuperhero(const char *name, short feetInHeight,
						   short inchesInHeight, const char *superpower,
						   const char *traits) {
	Superhero *superhero = malloc(sizeof(Superhero));

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
	if (superhero == NULL) {
		return;
	}
	free(superhero->traits);
	free(superhero->superpower);
	free(superhero->name);
	// free(superhero);

	// superhero = NULL;
}
