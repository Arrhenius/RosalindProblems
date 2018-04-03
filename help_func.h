#ifndef HELP_FUNC_H
	#define HELP_FUNC_H

// Max input sizes
#define MAX_LINE_SIZE 1024
#define MAX_TOKEN 10


// handle file constants
#define RD_ONLY 500
#define WR_ONLY 501


// Program choices
#define ID_DNA 200


int sreplace(char, char, char *);
//void openFileForRead(FILE *, const char *);
//void openFileForWrite(FILE *, const char *);
void handleFile(FILE **fp, const char *, int);

#endif
