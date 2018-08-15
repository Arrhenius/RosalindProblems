/*********************************
	Author	: Abel Atkinson
	Created	: March 31, 2018
*********************************/

#include <menu.h>
#include <ncurses.h>
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


// LookupTable names are based on rosalind ID names
// given to each problem on the website.
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

	char buffer[MAX_TOKEN];
/************************************************************
Note: Code present between the blocks of asterisks will be
to some extent experimental. It will contain the beginnings
of the ncurses menu and hopefully, a more refined interactive
program. None of this code will ever see the light of the 
main branch until it is completely functional. I type this 
with the intention of informing anyone of what's happening
should anyone be looking at this. This will be a slow
process since I still need to learn curses completely.
************************************************************/
	ITEM **my_items;
	MENU *my_menu;




	initscr();
	start_color();
	noecho();
	keypad(stdscr, TRUE);
	



/************************************************************

************************************************************/






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
