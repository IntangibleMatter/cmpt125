#include "a2_question2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// shoutout to wikipedia
const char *COLOR_TABLE[] = {
	"\x1b[0m",	"\x1b[40m", "\x1b[41m", "\x1b[42m", "\x1b[43m", "\x1b[44m",
	"\x1b[45m", "\x1b[46m", "\x1b[47m", "\x1b[30m", "\x1b[31m", "\x1b[32m",
	"\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[37m", NULL};

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

//#define PATTERN_SIZE 5;
// const Color pattern[] = {BLUE, MAGENTA, WHITE, MAGENTA, BLUE};
const Color pattern[] = {RED, YELLOW, YELLOW, GREEN, CYAN, BLUE, MAGENTA};

/*typedef enum {
	NONE,
} Pattern;*/

Superhero **superheroes;
int superhero_count = 0;

void deleteSuperhero(Superhero *superhero);
void printColored(char *string);
void printHeader();
int loadHeroes(Superhero **heroes[]);
int min(int a, int b);
void trimPrefix(char *string, char *prefix);
void printHero(Superhero *superhero);

int main(int argc, char *argv[]) {
	printHeader();
	Superhero **heroes = malloc(0);
	int heroCount = loadHeroes(&heroes);
	// Print them all out
	for (int i = 0; i < heroCount; i++) {
		printColored("=================================================\n");
		printf("%s", COLOR_TABLE[RED]);
		printf("Superhero #%d\n", i + 1);
		printf("%s", COLOR_TABLE[RESET]);
		printHero(heroes[i]);
	}
	// remove all the heroes
	for (int i = 0; i < heroCount; i++) {
		deleteSuperhero(heroes[i]);
	}
	free(heroes);
	return EXIT_SUCCESS;
}

int min(int a, int b) { return (a < b) ? a : b; }

void trimPrefix(char *string, char *prefix) {
	for (int i = 0; i < min(strlen(string), strlen(prefix)); i++) {
		if (string[i] != prefix[i]) {
			// prefix not complete, return
			return;
		}
		i++;
	}

	int offset = strlen(prefix);

	// less than or equal to so that the \0 gets moved too
	for (int i = 0; i < strlen(string) - offset; i++) {
		string[i] = string[i + offset];
	}
	string[strlen(string) - offset] = '\0';
}

int loadHeroes(Superhero **heroes[]) {
	printf("help\n");
	char lines[4][300]; // extra fifth line is for the blank separators
	int heroCount = 0;
	int done = 0;

	printf("heroes = %p\n", heroes);
	printf("*heroes = %p\n", *heroes);
	printf("**heroes = %p\n", **heroes);

	while (!done) {
		char donecheck[4] = "\0";
		for (int i = 0; i < 4; i++) {
			fgets(lines[i], 300, stdin);
		}
		// handle the extra line in between heroes and stop when the file is
		// done.
		if (fgets(donecheck, 4, stdin) == NULL) {
			done = 1;
		}
		heroCount++;

		*heroes = realloc(*heroes, heroCount * sizeof(Superhero *));

		trimPrefix(lines[0], "**Name:** ");
		trimPrefix(lines[1], "**Height:** ");
		trimPrefix(lines[2], "**Superpower:** ");
		int heightFeet;
		int heightInches;
		int numbuffer = 0;

		int i = 0;
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
		(*heroes)[heroCount - 1] = createSuperhero(
			lines[0], heightFeet, heightInches, lines[2], lines[3]);
	}
	*heroes = *heroes;
	return heroCount;
}

void printHero(Superhero *superhero) {
	printf("%s", COLOR_TABLE[GREEN]);
	printf("NAME: %s", superhero->name);
	printf("HEIGHT: %d feet, %d in\n", superhero->feetInHeight,
		   superhero->inchesInHeight);
	printf("POWER: %s", superhero->superpower);
	printf("TRAITS: %s", superhero->traits);
	printf("%s", COLOR_TABLE[RESET]);
}

void deleteSuperhero(Superhero *superhero) {
	if (superhero == NULL) {
		return;
	}

	clearSuperhero(superhero);

	free(superhero);
	superhero = NULL;
}

void printColored(char *string) {
	int i = 0;
	while (*(string + i) != '\0') {
		printf("%s", COLOR_TABLE[pattern[i % 7]]);
		printf("%c", *(string + i));
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
