/*****************************
	Author	: Abel Atkinson
	Created	: May 11, 2018
*****************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help_func.h"
#include "gc.h"



#if 1
// Initializes the dynamically allocated array 
struct geneticList *init_list(int num)
{
	struct geneticList *p;

	p = malloc(DLISTSZ(num));
	if(!p)
		return NULL;
	p->sz = 0;
	p->maxsz = num;
	return p;
}

#endif
// Inserts new geneticString data into the 
// dynamically allocated array geneticList.
int ins_list(struct geneticString data, struct geneticList **p)
{
	struct geneticList *q;
	
	if( (*p)->sz == (*p)->maxsz )
	{
		q = realloc(*p, DLISTSZ((*p)->maxsz + INCRSZ));
		if(!q)
		{
			fprintf(stderr,"Failed to realloc memory!! Terminating program!\n");
			exit(EXIT_FAILURE);
		}
		q->maxsz+=INCRSZ;
		*p = q;
	}
	
	(*p)->item[(*p)->sz++] = data;
	return 0;
}

void evaluateStrings(FILE *fpin, struct geneticList **p)
{
	// MAX_LINE_SIZE is a significant overkill for this 
	// portion of things since FASTA format would 
	// only be 80 chars per line read.
	char buffer[MAX_LINE_SIZE];
	char *ptr; // Pointer to move through buffer array
	struct geneticString data;
	data.name[0] = '\0';
	data.strSz = 0;
	data.g = 0;
	data.c = 0;
	data.gc_content = 0;
	
	if( !fpin )
	{
		fprintf(stderr,"file was unable to be read correctly!\n");
		exit(EXIT_FAILURE);
	}

	while( fgets(buffer, MAX_LINE_SIZE, fpin) )
	{

		// This is executed on each line to place null terminator
		if( !sreplace('\n','\0',buffer) )
		{
			fprintf(stderr,"Buffer overflow!\n");
			exit(EXIT_FAILURE);
		}

		// This should technically only be executed once which
		// would be at the very beginning of the run (Still
		// working on a more elegant solution).
		ptr = buffer;
		if( *ptr == '>' && data.name[0] == '\0' )
		{
			ptr++;
			strcpy(data.name, ptr);
		}
		// this should be the go to statement after the first name copy
		// occurs when reading in the file initially
		else if( *ptr == '>' && data.name[0] != '\0' )
		{
			ins_list(data, p);
			ptr++;
			strcpy(data.name, ptr);
			data.strSz = 0;
			data.g = 0;
			data.c = 0;
		}
		// If the line does not begin with a '>', it is assumed it is 
		// part of the dna string and program should go through each
		// character to count the G and C amounts present.
		else
		{
			while( *ptr )
			{
				if( *ptr == 'G' )
					data.g++;
				else if( *ptr == 'C' )
					data.c++;
				data.strSz++;
				ptr++;
			}
		}
	}
	ins_list(data, p);
}


struct geneticString evaluateHighestContent(struct geneticList **p)
{
	int i;
	float totalContent = 0.0; // Combined G and C count as float 
//	int g = 0;
//	int c = 0;
	int strSz = 0;      // Used this variable for readability
	int highest = 0;    // i value of of the highest gc content geneticString
	float cur = 0.0;    // current highest gc content value
	
	for(i=0; i<(*p)->sz; i++)
	{
		totalContent = (float)( (*p)->item[i].g + (*p)->item[i].c );
//		g = (*p)->item[i].g;
//		c = (*p)->item[i].c;
		strSz = (*p)->item[i].strSz;
		(*p)->item[i].gc_content = (float)( (totalContent / ((float)strSz)) * 100 );
		if( (*p)->item[i].gc_content > cur )
		{
			cur = (*p)->item[i].gc_content;
			highest = i;
		}
	}
	return (*p)->item[highest];
}



void runGC()
{
//	char buffer[MAX_LINE_SIZE];
	char file[MAX_LINE_SIZE];
	FILE *fpin = NULL;
	FILE *fpout = NULL;
	char tmp[5];

	struct geneticList *list;
	struct geneticString genStr;

	printf("Enter file to open: ");
	fgets(file, MAX_LINE_SIZE, stdin);
	handleString(file); // Make sure string is safe 
	
	// Open provided file for program execution
	handleFile(&fpin, file, RD_ONLY);
	printf("Computing GC content on file '%s'.....\n", file);

	list = init_list( INITSZ );
	evaluateStrings( fpin, &list );
	genStr = evaluateHighestContent( &list );

	printf("Done.\n\n");

	printf("Would you like to write results to file? (Yes/No): ");
	fgets(tmp, 5, stdin);
	handleString(tmp); // make sure string is safe

	if( (strcmp("Yes", tmp) == 0) || (strcmp("yes", tmp) == 0) ||
	    (strcmp("y", tmp) == 0) || (strcmp("Y", tmp) == 0 ) )
	{
		printf("\nWriting data results to file 'gc_content_results.txt'....\n");
		handleFile(&fpout, "gc_content_results.txt", WR_ONLY);
		fprintf(fpout,"%s\n%.6f\n", genStr.name, genStr.gc_content);
		fclose(fpout);
	}
	else
		printf("Output will not be written to file.\n\n");

	printf("GC content evaluation has completed.\n");
	fclose(fpin);
	free(list);
}


















