#include <stdio.h>
#include <stdlib.h>
#include "rna.h"
#include "help_func.h"


int dnaToRna(char *buffer)
{
	if( *buffer )
	{
		while( *buffer )
		{
			if( *buffer == 'T' )
				*buffer = 'U';
			buffer++;
		}
	}
	return 0;
}


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
	fclose(fpin);
	fclose(fpout);
}















