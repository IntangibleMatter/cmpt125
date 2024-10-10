#include "a2_question2.h"
#include <stdio.h>
#include <stdlib.h>

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
int loadHeroes(Superhero **heroes);
void trimPrefix(char *string, char *prefix);
void printHero(Superhero *superhero);

int main(int argc, char *argv[]) {
	printHeader();
	Superhero **heroes;
	int heroCount = loadHeroes(heroes);
	/*printf("argc: %d\n", argc);
	char str[256];
	while (1) {
		void *string = fgets(str, 256, stdin);
		printf("%s---!!---", str);
		if (string == NULL) {
			break;
		}
	}*/
	// tada
	return EXIT_SUCCESS;
}

void trimPrefix(char *string, char *prefix) {}

int loadHeroes(Superhero **heroes) {
	char lines[4][300]; // extra fifth line is for the blank separators
	int heroCount = 0;
	int done = 0;
	while (!done) {
		// printf(COLOR_TABLE[BG_CYAN]);
		// printf(COLOR_TABLE[BLACK]);
		// printf("Herocount: %d\n", heroCount);
		// printf(COLOR_TABLE[RESET]);
		// printf("checking\n");
		void *donecheck;
		// TODO: off by one error due to separating blank lines-- fix!
		for (int i = 0; i < 4; i++) {
			fgets(lines[i], 300, stdin);
			// printf("getting lines\n");
		}
		if (fgets(donecheck, 10, stdin) == NULL) {
			// printf("donecheck == null\n");
			done = 1;
		} // else {
		// printf("create hero\n");
		heroCount++;
		heroes = realloc(heroes, heroCount * sizeof(Superhero *));
		// printf("realloced\n");
		trimPrefix(lines[0], "**Name:** ");
		trimPrefix(lines[1], "**Height:** ");
		trimPrefix(lines[2], "**Superpower:** ");
		int heightFeet;
		int heightInches;
		int numbuffer = 0;

		int i = 0;
		while (lines[1][i] != '\0') {
			// printf("fixing number\n");
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
		// printf("Creating hero %d...\n", heroCount);
		heroes[heroCount - 1] = createSuperhero(
			lines[0], heightFeet, heightInches, lines[2], lines[3]);
		// printf("Created hero %d\n", heroCount);
		printHero(heroes[heroCount - 1]);
		//}
	}
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
