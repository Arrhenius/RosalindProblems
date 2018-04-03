/****************************************
	Author	: Abel Atkinson
	Created	: March 31, 2018
****************************************/
#include <stdio.h>
#include <stdlib.h>
#include "help_func.h"
//#include "err.h"		files need to be written


int sreplace(char old, char new, char *buffer)
{
	int count = 0;
	if( *buffer )
	{
		while( *buffer )
		{
			if( *buffer == old )
			{
				*buffer = new;
				count++;
			}
			buffer++;
		}
	}
	return count;
}

#if 0
void openFileForRead(FILE *fpin, const char *fileName)
{
	if( *fileName )
	{
		*fpin = fopen(fileName, "r");
		if(!fpin)
		{
			fprintf(stderr,"Failed to open file!\n");
			exit(EXIT_FAILURE);
		}
	}
}


void openFileForWrite(FILE *fpout, const char *fileName)
{
	if( *fileName )
	{
		*fpout = fopen(fileName, "w")
		if(!fpout)
		{
			fprintf(stderr,"Failed to open file for writing! Terminating.\n");
			exit(EXIT_FAILURE);
		}
	}
}

#endif

void handleFile(FILE **fp, const char *fileName, int action)
{
	if( *fileName )
	{
		switch(action)
		{
			case RD_ONLY:
				(*fp) = fopen(fileName, "r");
				break;
			case WR_ONLY:
				(*fp) = fopen(fileName, "w");
				break;
		}
		if( !(*fp) )
		{
			fprintf(stderr,"The file '%s' failed! Terminating.\n", fileName);
			exit(EXIT_FAILURE);
		}
	}
}
