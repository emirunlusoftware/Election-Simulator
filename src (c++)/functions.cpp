#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include "main.h"
using namespace std;



constexpr int MAX = 9;
char Digits[MAX], Step;
int index;

static void controlDigits()
{
	index = 0;

	while(1)
	{
		Digits[index] = _getch();

		if (Digits[index] == '\r' && index > 0) {
			cout << endl; break;
		}

		else if (Digits[index] == '\b' && index > 0) {
			cout << "\b \b";
			index--;
		}

		else if (isdigit(Digits[index]) && index < MAX)
		{
			if ( ( (Step == '1' || Step == '2') && (Digits[index] == '0' && index == 0) ) || (Step == '1' && index > 3) )
				continue;

			cout << Digits[index];
			index++;
		}
	}
}


int Number;
static inline int formatNumbers()
{
	Number = 0;

	for (int i = 0; i < index; i++) {
		Number = Number * 10 + (Digits[i] - '0');
	}

	return Number;
}


int Candidates, totalElectors, wonElectors, totalVotes, countedVotes, uncountedVotes, voteDifference;
vector <Candidate> Data;

void Election(Type x)
{
	cout.imbue(locale("en_US.UTF-8"));

	for (int i = 0; i < MAX; i++)
		Digits[i] = '\0';

	Step = '1'; countedVotes = 0;
	system("cls");



	switch(x)
	{
		case IndirectPresidental : cout << " ...INDIRECT PRESIDENTAL ELECTION..."; break;
		case DirectPresidental : cout << " ...DIRECT PRESIDENTAL ELECTION..."; break;
		case Parliamentary : cout << " ...PARLIAMENTARY ELECTION..."; break;
		case Referendum : cout << " ...REFERENDUM..."; break;
	} cout << endl << endl;


	if (x != Referendum)
	{
		cout << (x == Parliamentary ? ParliamentaryDialog[0] : PresidentalDialog[0]);
		controlDigits(); Candidates = formatNumbers();
	}
	else
		Candidates = 2;

	if (x == IndirectPresidental)
	{
		cout << PresidentalDialog[1];
		controlDigits(); totalElectors = formatNumbers();
	}
	Step++;

	while(1)
	{
		cout << Common[0];
		controlDigits(); totalVotes = formatNumbers();
		if (x == IndirectPresidental && totalVotes < totalElectors) {
			cout << "\n (ERROR: Total votes cannot be less than the electors.)\n";
			continue;
		}
		break;
	}
	Step++;


	vector <Candidate> Data(Candidates);

	for (int i = 0; i < Candidates; i++)
	{
		if (x != Referendum)
		{
			cout << endl;
			cout << (x == Parliamentary ? ParliamentaryDialog[1] : PresidentalDialog[2])
				 << i + 1 << ": ";
			getline(cin, Data[i].names);

			if (Data[i].names.length() > 75)
			{
				cout << "\n (ERROR: The name must be a maximum of 75 characters.)";
				i--; continue;
			}
		}
		else
			Data[i].names = ReferendumDialog[i+2];

		while (countedVotes != totalVotes)
		{
			if (x != Referendum)
				cout << Common[1] << Data[i].names << ": ";
			else
				cout << ReferendumDialog[i];

			controlDigits();
			Data[i].votes = formatNumbers(); countedVotes += Data[i].votes;

			if (countedVotes > totalVotes)
			{
				cout << "\n (ERROR: The " << (x == Referendum ? "choices'" : x == Parliamentary ? "parties'" : "candidates'")
					 << " total votes cannot exceed the total votes.)\n";
				countedVotes -= Data[i].votes; continue;
			}
			break;
		}
	}
	uncountedVotes = totalVotes - countedVotes;
	double Percent = 100 * (double)(countedVotes) / totalVotes,
		   Percent1 = 0;



	system("cls");
	cout << (x == Parliamentary ? ParliamentaryDialog[2] : PresidentalDialog[3]) << Candidates;
			(x == IndirectPresidental) ? (cout << PresidentalDialog[4] << totalElectors) : (cout << "")
		<< '\n' << Common[0] << totalVotes
		<< '\n' << Common[2] << countedVotes << " (" << fixed << setprecision(2) << Percent << "%)"
		<< '\n' << Common[3] << uncountedVotes << " (" << fixed << setprecision(2) << 100 - Percent << "%)\n";


	cout << endl << endl << " ...RESULTS...";

	sort(Data.begin(), Data.end(), [](const Candidate& a, const Candidate& b)
		{return a.votes > b.votes;} );

	for (int i = 0; i < Candidates; i++)
	{
		Percent = 100 * (double)(Data[i].votes) / countedVotes;

		if (i==0) Percent1 = Percent;

		cout << "\n " << Data[i].names << ": " << Data[i].votes;
		if (x == IndirectPresidental)
		{
			wonElectors = (int)((double)Data[i].votes / totalVotes * totalElectors);
			cout << " (" << wonElectors << "/" << totalElectors << ")";
		}
		else
			cout << " (" << fixed << setprecision(2) << Percent << "%)";
	}



	if (Candidates == 1)
	{
		cout << endl << endl << endl
			 << " " << Data[0].names << " won the election.";
	}

	else
	{
		voteDifference = Data[0].votes - Data[1].votes;
		int CoalitionVotes;
		cout << endl << endl << endl;

		if (x == IndirectPresidental || x == DirectPresidental)
		{

			if (uncountedVotes == 0)
			{
				if ( (x == DirectPresidental && Percent1 > 50)
					|| x == IndirectPresidental && ( (int)(100 * (double)Data[0].votes / totalVotes) > 50) )
					cout << " " << Data[0].names << " won the election.";
				else
					cout << " There is no winner.";
			}

			else if ((totalVotes / 2) > uncountedVotes + Data[0].votes)
				cout << " No one will win the election.";

			else if ((totalVotes / 2) < uncountedVotes + Data[0].votes && uncountedVotes < (totalVotes / 2))
			{
				if (Data[0].votes > totalVotes / 2)
					cout << " " << Data[0].names << " will definitely win the election.";

				else
					cout << " " << Data[0].names << " is closer to winning the election than the other candidates.";
			}

			else cout << " The winner is not definite...";
			
		}
		else if (x == Parliamentary)
		{
			if (uncountedVotes == 0)
			{
				if (Percent1 > 50)
					cout << "" << Data[0].names << " won the majority.";

				else
				{
					CoalitionVotes = 0;
					cout << " The possible coalition is: ";
					for (int i = 0; ; i++)
					{
						cout << Data[i].names;
						CoalitionVotes += Data[i].votes;

						if (CoalitionVotes > totalVotes / 2)
							break;

						cout << "-";
					}
				}
			}
			else if (voteDifference > uncountedVotes)
			{
				cout << " The vote difference between '" << Data[0].names << "' and '" << Data[1].names << "': " << voteDifference;
				cout << "\n " << Data[0].names << " will definitely win the election";

				if (Data[0].votes + uncountedVotes <= (totalVotes / 2))
				{
					cout << ", but not the majority.";

					CoalitionVotes = 0;
					cout << "\n The possible coalition is: ";
					for (int i = 0; ; i++)
					{
						cout << Data[i].names;
						CoalitionVotes += Data[i].votes;

						if (CoalitionVotes > totalVotes / 2)
							break;

						cout << "-";
					}
				}

				else if (Data[0].votes + uncountedVotes > (totalVotes / 2))
					cout << " and can guarantee the majority.";

				else cout << " and the majority.";
			}
			else cout << " The winner is not definite...";
		}
		else
		{
			if (uncountedVotes == 0 && voteDifference > 0)
				cout << " The " << Data[0].names << " votes won the referendum.";

			else if (uncountedVotes < voteDifference)
			{
				cout << " The vote difference between '" << Data[0].names << "' and '" << Data[1].names << "': " << voteDifference;
				cout << '\n' << " The " << Data[0].names << " votes will definitely win the referendum.";
			}

			else cout << " Hard to tell which one will win.";
		}
	}

	cout << endl << endl
		 << " (R)Retry\n (E)Exit";
}