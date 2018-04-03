/***************************************
	Author	: Abel Atkinson
	Created	: March 31, 2018
****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dna.h"
#include "help_func.h"
//#include "err.h"		files need to be written


struct DNA *initDataStructure()
{
	struct DNA *data;
	
	data = malloc(sizeof(struct DNA));
	if(!data)
	{
		fprintf(stderr,"Failed to initialize DNA structure! Terminating.\n");
		exit(EXIT_FAILURE);
	}
	data->a = 0;
	data->c = 0;
	data->g = 0;
	data->t = 0;
	return data;
}


/******************************************
	This function is what will go through
	the given DNA string to compute the
	amount of A, C, G, T present in the 
	provided string.

******************************************/

int countDNA(const char *buffer, struct DNA *data)
{
	if( *buffer )
	{
		while( *buffer )
		{
			if( *buffer == 'A' )
				data->a++;
			else if( *buffer == 'C' )
				data->c++;
			else if( *buffer == 'G' )
				data->g++;
			else if( *buffer == 'T' )
				data->t++;
			buffer++;
		}
	}
	else
		return 1;
	return 0;
}

/********************************************************

	This is the 'main' function for the dna count program

********************************************************/
void runDnaCount()
{
	struct DNA *data = NULL;
	char file[MAX_LINE_SIZE];
	char buffer[MAX_LINE_SIZE];
	char tmp[5];
	FILE *fpin = NULL;
	FILE *fpout = NULL;


	data = initDataStructure();
	if(!data)
	{
		fprintf(stderr,"Initialized data structure was not assigned correctly!\n");
		exit(EXIT_FAILURE);
	}

	// Ask for file to execute program on
	printf("Enter file to open: ");
	fgets(file, MAX_LINE_SIZE, stdin);
	
	// Check for buffer overflow
	if( !sreplace('\n','\0',file) )
	{
		fprintf(stderr,"Buffer overflow! Program Terminating.\n");
		exit(EXIT_FAILURE);
	}

	// Open provided file
   // openFileForRead(fpin, file);
	handleFile(&fpin, file, RD_ONLY);
	printf("....Running DNA count function on file '%s'\n", file);
	
	// read lines from file fpin and count DNA string
	while( fgets(buffer, MAX_LINE_SIZE, fpin) )
	{
		if( countDNA(buffer, data) != 0 )
		{
			fprintf(stderr,"Error reading from DNA string! Terminated.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	printf("Result: \tA = %d\n\tC = %d\n\tG = %d\n\tT = %d\n\t",
									data->a, data->c, data->g, data->t);

	// Write results to file if yes
	printf("Would you like to write results to file? (Yes/No): ");
	fgets(tmp, 5, stdin);
	if( !sreplace('\n','\0',tmp) )
	{
		fprintf(stderr,"Buffer overflow! Terminating!\n");
		exit(EXIT_FAILURE);
	}
	if( (strcmp("Yes",tmp) == 0) || (strcmp("yes",tmp) == 0) || 
		(strcmp("y",tmp) == 0) )
	{
		printf("Writing data results to file 'results.txt'....\n");
		handleFile(&fpout, "results.txt", WR_ONLY);
		fprintf(fpout, "%d %d %d %d\n", data->a, data->c, data->g, data->t);
		fclose(fpout);
	}
	else
		printf("Output will not be written to file.\n");
	
	printf("DNA count has completed.\n\n");
	fclose(fpin);
	free(data);
}

























