// Lyric Moysey-Rubin
// 301614885
// lwm2@sfu.ca
#include "a3_superherolib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Colours used from last assignment
// This is a table of ANSI terminal color codes, used to print things
// *in COLOUR!*
// shoutout to wikipedia for providing the codes.
const char *COLOR_TABLE[] = {"\x1b[0m",	 "\x1b[40m", "\x1b[41m", "\x1b[42m",
							 "\x1b[43m", "\x1b[44m", "\x1b[45m", "\x1b[46m",
							 "\x1b[47m", "\x1b[30m", "\x1b[31m", "\x1b[32m",
							 "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m",
							 "\x1b[37m", "\x1b[90m", NULL};

typedef enum {
	OK = 0,
	ERR_FAILED = 0xFF,
} ERRORS;

// All the colours in the above table. Used to index into it for access.
typedef enum {
	RESET,
	BG_BLACK,
	BG_RED,
	BG_GREEN,
	BG_YELLOW,
	BG_BLUE,
	BG_MAGENTA,
	BG_CYAN,
	BG_WHITE,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	GREY,
	COLOR_NULL,
} Color;

typedef enum {
	MODE_NONE,
	MODE_LOAD,
	MODE_SORT_HEIGHT,
	MODE_SORT_NAME,
	MODE_LOOKUP,
	MODE_INVALID,
	MODE_QUIT = -1,
} ProgramMode;

#define min(a, b) ((a < b) ? a : b)

ERRORS loadHeroes(char *filename);
void freeHeroArray(Superhero **heroes);
void freeAll();
void trimPrefix(char *string, char *prefix);
ProgramMode inputLoop();
bool heroesLoadedCheck();
void printHeader();
void clearInputBuff();
void printHero(Superhero *hero);
void printHeroes(Superhero **heroes);

// mode defs
void mode_loadHeroes();
void mode_sortHeight();
void mode_sortName();
void mode_Lookup();

Superhero **heroes;

// main loop
int main() {
	printHeader();

	ProgramMode mode = MODE_NONE;

	do {
		mode = MODE_NONE;
		mode = inputLoop();
		switch (mode) {
		case MODE_NONE:
			break;
		case MODE_LOAD:
			mode_loadHeroes();
			break;
		case MODE_SORT_HEIGHT:
			mode_sortHeight();
			break;
		case MODE_SORT_NAME:
			mode_sortName();
			break;
		case MODE_LOOKUP:
			mode_Lookup();
			break;
		case MODE_INVALID:
			if (heroesLoadedCheck()) {
				printf("%sERROR: invalid action. Please select a valid "
					   "action.%s\n",
					   COLOR_TABLE[RED], COLOR_TABLE[RESET]);
			} else {
				printf("%s", COLOR_TABLE[RED]);
				printf(
					"ERROR: No Superhero File loaded. Please load a file before\
 performing an action.\n");
				printf("%s", COLOR_TABLE[RESET]);
			}
			break;
		case MODE_QUIT:
			printf("Thank you for using The Superhero Database.\n");
			break;
		}

	} while (mode != MODE_QUIT);

	freeAll();
	// free(heroes);
	// heroes = NULL;

	return 0;
}

// open and load the hero file. Almost directly ripped from assingment 2.
ERRORS loadHeroes(char *filename) {
	if (heroes != NULL) {
		freeAll();
	}

	FILE *herofile;

	if ((herofile = fopen(filename, "r")) == NULL) {
		return ERR_FAILED;
	}

	char lines[4][300];

	// amount of heroes loaded so far
	int heroCount = 0;
	// done indicator
	bool done = false;

	while (!done) {
		// used to check if the file is finished being read
		char donecheck[4] = "\0";
		// get the next four lines in the file to read the hero
		for (int i = 0; i < 4; i++) {
			fgets(lines[i], 300, herofile);
			lines[i][strcspn(lines[i], "\n")] = '\0';
		}
		// handle the extra line in between heroes and stop when the file is
		// done.
		if (fgets(donecheck, 4, herofile) == NULL) {
			// sets the done flag
			done = true;
		}
		// incriment the hero count so we work on the next hero now
		heroCount++;

		// reallocate the memory
		heroes = realloc(heroes, heroCount * sizeof(Superhero *));

		// trim the starts of the lines so that they can be used later
		trimPrefix(lines[0], "**Name:** ");
		trimPrefix(lines[1], "**Height:** ");
		trimPrefix(lines[2], "**Superpower:** ");
		// variables for height
		int heightFeet;
		int heightInches;
		int numbuffer = 0;

		int i = 0;
		// ungodly function that I created to convert the two parts of the
		// height to numbers. Just miserable. don't worry about it.
		while (lines[1][i] != '\0') {
			char chr = lines[1][i];
			i++;
			if (chr == '\'') {
				heightFeet = numbuffer;
				numbuffer = 0;
				continue;
			} else if (chr == '"') {
				heightInches = numbuffer;
				break;
			} else {
				numbuffer *= 10; // move place value over
				if ('0' <= chr && chr <= '9') {
					numbuffer += chr - '0';
				}
			}
		}
		// add the new hero to the array
		Superhero *newhero = createSuperhero(lines[0], heightFeet, heightInches,
											 lines[2], lines[3]);
		heroes[heroCount - 1] = newhero;
	}

	printf("Loaded %d heroes from %s.\n", heroCount, filename);

	heroes = realloc(heroes, (heroCount + 1) * sizeof(Superhero *));
	heroes[heroCount] = NULL;

	fclose(herofile);
	return OK;
}

// trims a prefix from a string if it exists.
void trimPrefix(char *string, char *prefix) {
	// run for the entire length of whichever string is shorter.
	// If the covered area overlaps completely, erase that section
	// from string.
	for (int i = 0; i < min(strlen(string), strlen(prefix)); i++) {
		if (string[i] != prefix[i]) {
			// prefix not complete, return
			return;
		}
	}

	// the offset from the start of the string where it should start now
	int offset = strlen(prefix);

	// move characters around to get rid of the prefix.
	for (int i = 0; i < strlen(string) - offset; i++) {
		string[i] = string[i + offset];
	}
	// set last character to be '\0' so that there's no weird double strings
	string[strlen(string) - offset] = '\0';
}

/*
 * Gets the input for the mode to switch to, as well as printing out the data
 * for which modes you *can* switch to.
 *
 */
ProgramMode inputLoop() {
	printf("Please select an option (press 1-5) and press enter.\n");
	printf("1) Load a heroes file.\n");
	bool heroesLoaded = !(heroes == NULL || heroes[0] == NULL);
	if (!heroesLoaded) {
		// grey out the unusable options if they're unusable.
		printf("%s", COLOR_TABLE[GREY]);
	}
	printf("2) List heroes by height.\n");
	printf("3) List heroes by name.\n");
	printf("4) Search heroes by power.\n");
	printf("%s", COLOR_TABLE[RESET]);

	printf("5) Exit the program.\n");
	printf("\nPlease enter the number for the mode you want: ");

	int ans = MODE_NONE;
	if (scanf("%d", &ans) == 0) {
		clearInputBuff();
		return MODE_INVALID;
	}
	clearInputBuff();
	if (heroesLoaded) {
		switch (ans) {
		case 1:
			return MODE_LOAD;
			break;
		case 2:
			return MODE_SORT_HEIGHT;
			break;
		case 3:
			return MODE_SORT_NAME;
			break;
		case 4:
			return MODE_LOOKUP;
			break;
		case 5:
			return MODE_QUIT;
			break;
		default:
			return MODE_INVALID;
			break;
		}
	} else {
		switch (ans) {
		case 1:
			return MODE_LOAD;
			break;
		case 5:
			return MODE_QUIT;
			break;
		default:
			return MODE_INVALID;
		}
	}
	return MODE_INVALID;
}

// asserts that the heroes file is loaded, alerts if not
bool heroesLoadedCheck() {
	if (heroes == NULL || heroes[0] == NULL) {
		return false;
	}
	return true;
}

// frees all the heroes and the hero array
void freeAll() {
	if (heroes == NULL) {
		return;
	}
	int idx = 0;

	while (heroes[idx] != NULL) {
		removeSuperhero(heroes[idx]);
		heroes[idx] = NULL;
		idx++;
	}
	free(heroes);
	heroes = NULL;
}

// does what it says on the tin
void printHeader() {
	printf("|============================================================|\n");
	printf("|==================== Lyric Moysey-Rubin ====================|\n");
	printf("|========================= 301614885 ========================|\n");
	printf("|=========================== lwm2 ===========================|\n");
	printf(
		"|============================================================|\n\n");
}

// handles the state for loading heroes from a file.
void mode_loadHeroes() {
	char fname[255]; // max name length of an individual file in Linux
	printf("Please input the file name: ");
	if (scanf("%s", fname)) {
		// printf("file name: %s\n", fname);
		ERRORS err = loadHeroes(fname);
		if (err != OK) {
			printf("Couldn't load file %s.\n", fname);
		}
	} else {
		printf("Invalid input.\n");
	}
}

// sort them by height and print
void mode_sortHeight() {
	sortSuperheros(heroes, compareSuperheroesByHeight);
	printHeroes(heroes);
}

// sort them by name and print
void mode_sortName() {
	sortSuperheros(heroes, compareSuperheroesByName);
	printHeroes(heroes);
}

// get the input for the lookup, call the search function, then free the result
void mode_Lookup() {
	char input[50];
	printf("Please enter a substring of the power you want to look for: ");
	if (scanf("%s", input)) {
		Superhero **results = lookupSuperheroBySuperpower(
			heroes, getHeroArraySize(heroes), input);
		if (getHeroArraySize(results) > 0) {
			printHeroes(results);
		} else {
			printf("Could not find any heroes matching \"%s\".\n", input);
		}
		free(results);
	}
}

// clears the input buffer so that there isn't an infinite loop.
// shoutout geeksforgeeks:
// https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
void clearInputBuff() {
	while ((getchar()) != '\n')
		;
}

// loops through an array of heroes, printing them all.
void printHeroes(Superhero **heroArr) {
	if (heroArr == NULL) {
		return;
	}

	int idx = 0;
	while (heroArr[idx] != NULL) {
		printHero(heroArr[idx]);
		idx++;
	}
}

// prints the info about a hero.
void printHero(Superhero *superhero) {
	// make it print green because that's cool
	printf("%s", COLOR_TABLE[GREEN]);
	printf("NAME: %s\n", superhero->name);
	printf("HEIGHT: %d feet, %d in\n", superhero->feetInHeight,
		   superhero->inchesInHeight);
	printf("POWER: %s\n", superhero->superpower);
	printf("TRAITS: %s\n", superhero->traits);
	printf("===\n");
	// remove the colour printing
	printf("%s", COLOR_TABLE[RESET]);
}
