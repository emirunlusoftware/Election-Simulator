#ifndef main_h
#define main_h

#include <string>
#include <iostream>
#include <conio.h>
using namespace std;


struct Candidate
{
	long long votes = 0;
	string names;
};

enum Type {
	IndirectPresidental,
	DirectPresidental,
	Parliamentary,
	Referendum
};


extern const char* MainMenu[];
extern const char* Common[];
extern const char* PresidentalDialog[];
extern const char* ParliamentaryDialog[];
extern const char* ReferendumDialog[];

void Election(Type x);

#endif