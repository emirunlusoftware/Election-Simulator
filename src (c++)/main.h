#ifndef main_h
#define main_h
using namespace std;


struct Candidate
{
	int votes = 0;
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

extern
	void
	Election(Type x),
	MainMenu();

#endif