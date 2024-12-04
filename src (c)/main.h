#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


typedef struct {
	long long votes;
	char names[75];
} Candidate;

typedef enum {
	IndirectPresidental,
	DirectPresidental,
	Parliamentary,
	Referendum
} Type;


extern const char* MainMenu[];
extern const char* Common[];
extern const char* PresidentalDialog[];
extern const char* ParliamentaryDialog[];
extern const char* ReferendumDialog[];

void Election(Type x);

#endif