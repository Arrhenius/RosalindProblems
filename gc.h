/****************************
	Author	: Abel Atkinson
	Created	: May 11, 2018
****************************/

#ifndef GC_H
	#define GC_H

struct geneticString
{
	char name[64];
	int strSz;
	int g;
	int c;
	float gc_content;
};


struct geneticList
{
	int sz;
	int maxsz;
	struct geneticString item[1];
};

#define INITSZ 6
#define INCRSZ 9
#define DLISTSZ(n) ( (size_t)sizeof(struct geneticList) + \
                   ((n-1) * (size_t)sizeof(struct geneticString)) )

struct geneticList *init_list(int num);
int ins_list(struct geneticString data, struct geneticList **p);
void evaluateStrings(FILE *fpin, struct geneticList **p);
struct geneticString evaluateHighestContent(struct geneticList **p);
void runGC();


#endif
