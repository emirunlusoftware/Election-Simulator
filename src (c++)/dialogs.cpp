#include <iostream>
#include "main.h"
using namespace std;


void MainMenu()
{
	cout << " CHOOSE THE ELECTION TYPE\n\n"
		 << " (1)Indirect Presidental\n"
		 << " (2)Direct Presidental\n"
		 << " (3)Parliamentary\n"
		 << " (4)Referendum\n\n"
		 << " (E)Exit";
}

const char* Common[]
{
	" Total Votes: ",
	" Total vote of ",
	" Counted Votes: ",
	" Uncounted Votes: "
};

const char* PresidentalDialog[]
{
	" Number of Candidates: ",
	" Number of Electors: ",
	" Enter the name of the Candidate ",
	" Candidates: ",
	"\n Electors: "
};

const char* ParliamentaryDialog[]
{
	" Number of Political Parties: ",
	" Enter the name of the Party ",
	" Political Parties: "
};

const char* ReferendumDialog[]
{
	" Total vote of Yes: ",
	" Total vote of No: ",
	"Yes",
	"No"
};