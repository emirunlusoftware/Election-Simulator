#include <string>
#ifndef main_h
#define main_h
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


extern const char* Common[];
extern const char* PresidentalDialog[];
extern const char* ParliamentaryDialog[];
extern const char* ReferendumDialog[];

extern inline int formatNumbers();

extern inline void MainMenu();
extern void Election(Type x);

#endif