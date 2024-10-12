// Lyric Moysey-Rubin
// lwm2
// 301614885

#include "a2_question2.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// This is a table of ANSI terminal color codes, used to print things
// *in COLOUR!*
// shoutout to wikipedia for providing the codes.
const char *COLOR_TABLE[] = {
	"\x1b[0m",	"\x1b[40m", "\x1b[41m", "\x1b[42m", "\x1b[43m", "\x1b[44m",
	"\x1b[45m", "\x1b[46m", "\x1b[47m", "\x1b[30m", "\x1b[31m", "\x1b[32m",
	"\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[37m", NULL};

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
	COLOR_NULL,
} Color;

// The pattern used for printColored(). Used as indexes into COLOR_TABLE
const Color pattern[] = {RED, YELLOW, YELLOW, GREEN, CYAN, BLUE, MAGENTA};

// the array of superheroes
Superhero **superheroes;
// how many superheroes there are
int superhero_count = 0;

// Deletes a hero and sets the pointer to NULL
void deleteSuperhero(Superhero *superhero);
// Prints text prettily using terminal colours
void printColored(char *string);
// Prints the header
void printHeader();
// Loads the heroes into a dynamically allocated array of pointers.
// RETURN: the amount of heroes that were loaded
int loadHeroes(Superhero **heroes[]);
// Minimum value function. Returns the smaller of a and b
int min(int a, int b);
// Trims a prefix from the start of a string. If the whole prefix doesn't exist
// at the start of the string, does nothing. Otherwise modifies the string to
// lose the prefix.
void trimPrefix(char *string, char *prefix);
// Prints the information about a suoerhero to the terminal.
void printHero(Superhero *superhero);

int main() {
	printHeader();
	Superhero **heroes = malloc(0);
	int heroCount = loadHeroes(&heroes);
	// Print them all out
	for (int i = 0; i < heroCount; i++) {
		// separator
		printColored("=================================================\n");
		// make the number red
		printf("%s", COLOR_TABLE[RED]);
		printf("Superhero #%d\n", i + 1);
		// reset the colour before printing the heroes
		printf("%s", COLOR_TABLE[RESET]);
		printHero(heroes[i]);
	}
	// remove all the heroes
	for (int i = 0; i < heroCount; i++) {
		deleteSuperhero(heroes[i]);
	}
	// remove the array
	free(heroes);
	// we did it!
	return EXIT_SUCCESS;
}

// a minimal min value function
int min(int a, int b) { return (a < b) ? a : b; }

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

// loads the heroes into a provided array
int loadHeroes(Superhero **heroes[]) {
	// the file which the heroes are located in
	FILE *herofile;

	// Open the file to read it. Null safety check included.
	// credit to https://www.programiz.com/c-programming/c-file-input-output
	// for the refresher on file loading
	if ((herofile = fopen("./superheros.txt", "r")) == NULL) {
		printf("Error! File 'superheros.txt' does not exist! Exiting!\n");
		fclose(herofile);
		return 0;
	}

	// four lines per hero with maximum 300 characters
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
		*heroes = realloc(*heroes, heroCount * sizeof(Superhero *));

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
		(*heroes)[heroCount - 1] = newhero;
	}
	// finish up
	fclose(herofile);
	*heroes = *heroes;
	return heroCount;
}

void printHero(Superhero *superhero) {
	// make it print green because that's cool
	printf("%s", COLOR_TABLE[GREEN]);
	printf("NAME: %s", superhero->name);
	printf("HEIGHT: %d feet, %d in\n", superhero->feetInHeight,
		   superhero->inchesInHeight);
	printf("POWER: %s", superhero->superpower);
	printf("TRAITS: %s", superhero->traits);
	// remove the colour printing
	printf("%s", COLOR_TABLE[RESET]);
}

// deletes a hero
void deleteSuperhero(Superhero *superhero) {
	// make sure it isn't null
	if (superhero == NULL) {
		return;
	}

	// clear the hero
	clearSuperhero(superhero);

	// delete the hero itself
	free(superhero);
	superhero = NULL;
}

// prints things using a colour pattern
void printColored(char *string) {
	int i = 0;
	// loop over the whole string
	while (*(string + i) != '\0') {
		// This prints the correct component in the pattern
		// I had to use a hard-coded number because it freaked out
		// whenever i defined it as a constant or with a #DEFINE for some
		// reason.
		printf("%s", COLOR_TABLE[pattern[i % 7]]);
		// prints the next character in the string
		printf("%c", *(string + i));
		// reset the colours so we can be clean
		printf("%s", COLOR_TABLE[RESET]);
		i++;
	}
};

void printHeader() {
	/*
	 * Looks like this:
	 * ╔═════════════════════════════════════════════════════════════════════╗
	 * ╠════════════════════════► LYRIC MOYSEY-RUBIN ◄═══════════════════════╣
	 * ╠════════════════════════════► 301614885 ◄════════════════════════════╣
	 * ╠═══════════════════════════► lwm2@sfu.ca ◄═══════════════════════════╣
	 * ╚═════════════════════════════════════════════════════════════════════╝
	 *
	 * Though this version has been shortened because of the 80-character line
	 * limit
	 * Gotta do the unicode codepoints because c.
	 * */

	printColored("\u2554\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2557\n");
	printColored("\u2560\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u25BA\
 LYRIC MOYSEY-RUBIN \
\u25C4\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2563\n");

	printColored("\u2560\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u25BA\
 301614885 \
\u25C4\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2563\n");
	printColored("\u2560\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u25BA\
 lwm2@sfu.ca \
\u25C4\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2563\n");
	printColored("\u255A\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\
\u255D\n");
}
