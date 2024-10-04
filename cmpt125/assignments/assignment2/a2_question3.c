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
const Color pattern[] = {BLUE, MAGENTA, WHITE, MAGENTA, BLUE};
// const Color pattern[] = {RED, YELLOW, YELLOW, GREEN, CYAN, BLUE, MAGENTA};

/*typedef enum {
	NONE,
} Pattern;*/

Superhero **superheroes;
int superhero_count = 0;

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
		printf("%s", COLOR_TABLE[pattern[i % 5]]);
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

int main(int argc, char *argv[]) {
	printHeader();
	// tada
	return EXIT_SUCCESS;
}
