/*********************************
	Author	: Abel Atkinson
	Created	: March 31, 2018
*********************************/

// If compiling using visual studio, tell the compiler not to give
// its warnings about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dna.h"
#include "gc.h"
#include "hamm.h"
#include "rna.h"
#include "revc.h"
#include "display.h"
#include "help_func.h"


// The following structure is in the searchTable function
// to help look up the program that needs to be executed
// when an option is entered.
// 
// Note: LookupTable names are based on rosalind ID names
//       given to each problem on the website.
static struct
{
	char name[MAX_TOKEN];
	int val;

} lookupTable[] =
{
		{ "DNA",    ID_DNA },
		{ "RNA",    ID_RNA },
		{ "REVC",   ID_REVC },
		{ "GC",     ID_GC },
		{ "HAMM",   ID_HAMM },
		{ "PROT",   ID_PROT },
		{ "SUBS",   ID_SUBS },
		{ "PRTM",   ID_PRTM }
};

/*********************** searchTable **********************
int searchTable(const char *buffer)
Purpose:
	Takes a string obtained from user to search the
	lookupTable for a matching string. The matching string
	would be the program of choice and would then be executed

Parameters:
	I	const char *buffer	The user inputted string

Returns:
	0 Normal return
***********************************************************/
int searchTable(const char *buffer)
{
	int i;
	for(i=0; lookupTable[i].name != '\0'; i++)
	{
		if( strcmp(buffer, lookupTable[i].name) == 0 )
			return lookupTable[i].val;
	}
	return 0;
}


/* main for entire program */
int main(int argc, char *argv[])
{
	char buffer[MAX_TOKEN];


	printAbout();
	printOptions();
	printf("\n\nEnter a choice from the list above: ");
	fgets(buffer, MAX_TOKEN, stdin);
	if( !sreplace('\n','\0',buffer) )
	{
		fprintf(stderr,"Buffer overflow!\n");
		exit(EXIT_FAILURE);
	}
	
	switch(searchTable(buffer))
	{
		case ID_DNA:
			runDnaCount();
			break;
		case ID_RNA:
			runDnaToRna();
			break;
		case ID_REVC:
			runRevc();
			break;
		case ID_GC:
			runGC();
			break;
		case ID_HAMM:
			runHammingDistance();
			break;
		case ID_PROT:
			break;
		case ID_SUBS:
			break;
		case ID_PRTM:
			break;
		default:
			printf("'%s' is an invalid choice.\n", buffer);
	}

	printf("Program is now closing\n");
	return EXIT_SUCCESS;
}
