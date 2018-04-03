#ifndef DNA_H
	#define DNA_H 

struct DNA
{
	int a;
	int c;
	int g;
	int t;
};

struct DNA *initDataStructures();
int countDNA(const char *, struct DNA *);
void runDnaCount();

#endif
