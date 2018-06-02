/********************************
	Author	: Abel Atkinson
	Created	: May 2, 2018
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "revc.h"
#include "help_func.h"


int revc(const char *buffer, char *comp)
{
	char *q;
	int i;
	q = comp;
	for(i = strlen(buffer) - 1; i >= 0; i--, q++)
	{
		if( buffer[i] == 'A' )
			*q = 'T';
		else if( buffer[i] == 'T' )
			*q = 'A';
		else if( buffer[i] == 'G' )
			*q = 'C';
		else if( buffer[i] == 'C' )
			*q = 'G';
	}
	*q = '\0';
	return 0;
}


void runRevc()
{
	char file[MAX_LINE_SIZE];
	char buffer[MAX_LINE_SIZE];
	char comp[MAX_LINE_SIZE];
	FILE *fpin = NULL;
	FILE *fpout = NULL;

	printf("Enter file to open: ");
	fgets(file, MAX_LINE_SIZE, stdin);

	if( !sreplace('\n','\0',file) )
	{
		fprintf(stderr,"Buffer overflow! Program Terminating.\n");
		exit(EXIT_FAILURE);
	}

	// Open provided file for program execution
	handleFile(&fpin, file, RD_ONLY);
	handleFile(&fpout, "revc_results.txt", WR_ONLY);
	printf("....Running REVC program conversion on data file '%s'\n", file);
	printf("....Printing results to 'revc_results.txt'\n");

	// Read from file and convert each line one at a time.
	// Upon line conversion immediately print output to file
	while( fgets(buffer, MAX_LINE_SIZE, fpin) )
	{
		if( !sreplace('\n','\0',buffer) )
		{
			fprintf(stderr,"Buffer overflow! Program Terminating.\n");
			exit(EXIT_FAILURE);
		}

		revc(buffer, comp);
		fprintf(fpout, "%s\n", comp);
	}

	printf(" REVC program complete. Results stored to file.\n");
	fclose(fpin);
	fclose(fpout);
}
