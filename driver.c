#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dna.h"
#include "display.h"
#include "help_func.h"


static struct
{
	char name[MAX_TOKEN];
	int val;

} lookupTable[] =
{
		{ "DNA", ID_DNA }
};
 
/* search for inputted string in the lookupTable */
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
	char buffer[MAX_LINE_SIZE];


	printAbout();
	printOptions();
	printf("\n\nEnter a choice from the list above: ");
	fgets(buffer, MAX_LINE_SIZE, stdin);
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
		default:
			printf("'%s' is an invalid choice.\n", buffer);
	}

	return EXIT_SUCCESS;
}
