#include <string.h>
#ifndef main_h
#define main_h


typedef struct Candidate
{
	long long votes;
	char names[75];
} Candidate;

typedef enum Type {
	IndirectPresidental,
	DirectPresidental,
	Parliamentary,
	Referendum
} Type;

extern const char* Common[];
extern const char* PresidentalDialog[];
extern const char* ParliamentaryDialog[];
extern const char* ReferendumDialog[];

extern inline int formatNumbers();

extern inline void MainMenu();
extern void Election(Type x);

#endif