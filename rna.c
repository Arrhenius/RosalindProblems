#include <stdio.h>
#include <stdlib.h>
#include "rna.h"
#include "help_func.h"

/******************* dnaToRna ****************
int dnaToRna(char *buffer)

Purpose:
	Convert dna string to an rna one

Parameters:
	I	char *buffer	dna string to convert

Returns:
	Automatically returns 0 for success

Note to self: Consider a better return for
	this function.
*********************************************/
int dnaToRna(char *buffer)
{
	// Check to see if string exists
	if( *buffer )
	{
		while( *buffer )
		{
			// If char in string has a 'T' as
			// a character, change to 'U'
			if( *buffer == 'T' )
				*buffer = 'U';
			buffer++; // move to next char in string
		}
	}
	return 0;
}


/****************** runDnaToRna **************
void runDnaToRna()

Purpose:
	Main calling function to run program that
	changes DNA string to an RNA one

Parameters:
	N/A

Returns:
	N/A
*********************************************/

void runDnaToRna()
{
	char file[MAX_LINE_SIZE];
	char buffer[MAX_LINE_SIZE];
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
	handleFile(&fpout, "dna_to_rna_results.txt", WR_ONLY);
	printf("....Running DNA to RNA program conversion on file '%s'\n", file);
	printf("....Printing results to 'dna_to_rna_results.txt'\n");
	
	// Read from file and convert each line one at a time.
	// Upon line conversion immediately print output to file
	while( fgets(buffer, MAX_LINE_SIZE, fpin) )
	{
		if( !sreplace('\n','\0',buffer) )
		{
			fprintf(stderr,"Buffer overflow! Program terminated.");
			exit(EXIT_FAILURE);
		}
		dnaToRna(buffer);
		fprintf(fpout,"%s\n",buffer);
	}

	printf("DNA to RNA conversion complete. Results stored to file.\n");
	// Close files since they are no longer needed
	fclose(fpin); 
	fclose(fpout);
}















