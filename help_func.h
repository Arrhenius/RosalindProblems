#ifndef HELP_FUNC_H
	#define HELP_FUNC_H

// Max input sizes
#define MAX_LINE_SIZE 1024
#define MAX_TOKEN 10


// handle file constants
#define RD_ONLY 500
#define WR_ONLY 501


// Program choices
#define ID_DNA    200
#define ID_RNA    201
#define ID_REVC   202
#define ID_GC     203
#define ID_HAMM   204
#define ID_PROT   205
#define ID_SUBS   206
#define ID_PRTM   207


int sreplace(char old, char newChar, char *buffer);
//void openFileForRead(FILE *, const char *);
//void openFileForWrite(FILE *, const char *);
void handleFile(FILE **fp, const char *fileName, int action);
void handleString(char *buffer);

#endif
