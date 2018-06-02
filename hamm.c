#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help_func.h"




unsigned int computeHammingDistance(FILE *file)
{
	unsigned int hamDis = 0;
	int i = 0;
	char s1[MAX_LINE_SIZE]; // Dna string 1
	char s2[MAX_LINE_SIZE]; // Dna string 2
	
	fgets(s1, MAX_LINE_SIZE, file);
	fgets(s2, MAX_LINE_SIZE, file);
	handleString(s1); // Make string safe
	handleString(s2); // Make string safe 

	while( s1[i] && s2[i] )
	{
		if( s1[i] != s2[i] )
			hamDis++;
		i++;
	}

#if 0
	while( *s1 && *s2 )
	{
		if( *s1 != *s2 )
			hamDis++;
		s1++;
		s2++;
	}
#endif
	return hamDis;
}


void runHammingDistance()
{
	char file[MAX_LINE_SIZE];
	FILE *fpin = NULL;
	FILE *fpout = NULL;
	char tmp[MAX_TOKEN];

	unsigned int result = 0;
	
	printf("Enter file to open: ");
	fgets(file, MAX_LINE_SIZE, stdin);
	handleString(file); // Make sure string is safe

	// Open provided file for program execution
	handleFile(&fpin, file, RD_ONLY);
	printf("Computing Hamming distance on provided file '%s'.....\n", file);
	
	result = computeHammingDistance(fpin);
	fclose(fpin);
	printf("Done.\n");

	printf("Hamming Distance results: %u\n\n", result);
	

	printf("Would you like to write results to file? (Yes/No): ");
	fgets(tmp, MAX_TOKEN, stdin);
	handleString(tmp);
	
	if( (strcmp("Yes", tmp) == 0) || (strcmp("yes", tmp) == 0) ||
	    (strcmp("y", tmp) == 0) || (strcmp("Y", tmp) == 0) )
	{
		printf("\nWriting results to file 'hamm_results.txt'....\n");
		handleFile(&fpout, "hamm_results.txt", WR_ONLY);
		fprintf(fpout, "%u\n", result);
		fclose(fpout);
	}
	else
		printf("Results were not written to file\n"); 

	printf("Program has completed.\n");
}
