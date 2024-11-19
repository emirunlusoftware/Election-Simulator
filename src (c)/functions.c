#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include "main.h"

#define MAX 9

char Step, Digits[MAX];
int index;

static void controlDigits()
{
	index = 0;

	while(1)
	{
		Digits[index] = _getch();

		if (Digits[index] == '\r' && index > 0) {
			printf("\n"); break;
		}

		else if (Digits[index] == '\b' && index > 0) {
			printf("\b \b");
			index--;
		}

		else if (isdigit(Digits[index]) && index < MAX)
		{
			if ( ( (Step == '1' || Step == '2') && (Digits[index] == '0' && index == 0) ) || (Step == '1' && index > 3) )
				continue;

			printf("%c",Digits[index]);
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


Candidate* Data;
static int Sorting(const void* a, const void* b)
{
	const Candidate* candidateA = (const Candidate*)a;
	const Candidate* candidateB = (const Candidate*)b;

	if (candidateA->votes < candidateB->votes)
		return 1;
	else if (candidateA->votes > candidateB->votes)
		return -1;
	else
		return 0;
}


int totalElectors, wonElectors, wonElectors1, countedVotes, uncountedVotes, voteDifference,
Candidates = 0; currentCandidates;
long long totalVotes;

void Election(Type x)
{
	Data = NULL;

	for (int i = 0; i < MAX; i++)
		Digits[i] = '\0';

	Step = '1'; countedVotes = 0;
	system("cls");



	switch(x)
	{
		case IndirectPresidental : printf(" ...INDIRECT PRESIDENTAL ELECTION..."); break;
		case DirectPresidental : printf(" ...DIRECT PRESIDENTAL ELECTION..."); break;
		case Parliamentary : printf(" ...PARLIAMENTARY ELECTION..."); break;
		case Referendum : printf(" ...REFERENDUM..."); break;
	} printf("\n\n");


	if (x != Referendum)
	{
		printf("%s", (x == Parliamentary ? ParliamentaryDialog[0] : PresidentalDialog[0]));
		controlDigits(); Candidates = formatNumbers();
	}
	else
		Candidates = 2;

	if (x == IndirectPresidental)
	{
		printf("%s", PresidentalDialog[1]);
		controlDigits(); totalElectors = formatNumbers();
	}
	Step++;

	while(1)
	{
		printf("%s", Common[0]);
		controlDigits(); totalVotes = formatNumbers();
		if (x == IndirectPresidental && totalVotes < totalElectors) {
			printf("\n (ERROR: Total votes cannot be less than the electors.)\n");
			continue;
		}
		break;
	}
	Step++;

	for (currentCandidates = 0; currentCandidates < Candidates; currentCandidates++)
	{
		Data = realloc(Data, (currentCandidates + 1) * sizeof(Candidate));
		if (Data == NULL) {
			printf("Memory Allocation ERROR!\n");
			free(Data); exit(EXIT_FAILURE);
		}

		printf("\n");

		if (x != Referendum)
		{
			printf("%s%d: ", (x == Parliamentary ? ParliamentaryDialog[1] : PresidentalDialog[2]), currentCandidates+1);
			fgets(Data[currentCandidates].names, sizeof(Data[currentCandidates].names), stdin);

			size_t DataLength = strlen(Data[currentCandidates].names);
			if (DataLength > 0 && Data[currentCandidates].names[DataLength - 1] == '\n')
				Data[currentCandidates].names[DataLength - 1] = '\0';

			if (strlen(Data[currentCandidates].names) > 75)
			{
				printf("\n (ERROR: The name must be a maximum of 75 characters.)");
				currentCandidates--; continue;
			}
		}
		else
			strcpy_s(Data[currentCandidates].names, 75, ReferendumDialog[currentCandidates + 2]);

		while (countedVotes != totalVotes)
		{
			if (x != Referendum)
				printf("%s%s: ", Common[1], Data[currentCandidates].names);
			else
				printf("%s", ReferendumDialog[currentCandidates]);

			controlDigits();
			Data[currentCandidates].votes = formatNumbers(); countedVotes += Data[currentCandidates].votes;

			if (countedVotes > totalVotes)
			{
				printf("\n (ERROR: The %s", (x == Referendum ? "choices'" : x == Parliamentary ? "parties'" : "candidates'"));
				printf(" total votes cannot exceed the total votes.)\n");
				countedVotes -= Data[currentCandidates].votes; continue;
			}
			break;
		}
	}
	uncountedVotes = totalVotes - countedVotes;
	double Percent = 100 * (double)(countedVotes) / totalVotes,
		   Percent1 = 0;


	system("cls");
	switch (x)
	{
		case IndirectPresidental:
		case DirectPresidental:
		{
			printf("%s%d\n", PresidentalDialog[3], Candidates);

			if (x == IndirectPresidental)
				printf("%s%d\n", PresidentalDialog[4], totalElectors); break;

			break;
		}
		case Parliamentary:
			printf("%s%d\n", ParliamentaryDialog[2], Candidates); break;
		case Referendum: break;
	}

	printf("%s%lld", Common[0], totalVotes);
	printf("\n%s%d (%.2f%%)", Common[2], countedVotes, Percent);
	printf("\n%s%d (%.2f%%)\n", Common[3], uncountedVotes, 100 - Percent);

	qsort(Data, Candidates, sizeof(Candidate), Sorting);
	printf("\n\n ...RESULTS...");

	for (int i = 0; i < Candidates; i++)
	{
		Percent = (countedVotes == 0) ? 0 : 100 * (double)(Data[i].votes) / countedVotes;
		printf("\n %s: %lld", Data[i].names, Data[i].votes);

		if (i == 0) Percent1 = Percent;

		if (x == IndirectPresidental)
		{
			wonElectors = (Data[i].votes * totalElectors) / totalVotes;
			printf(" (%d/%d)", wonElectors, totalElectors);

			if (i == 0) wonElectors1 = wonElectors;
		}
		else
			printf(" (%.2f%%)", Percent);
	}



	if (Candidates == 1)
		printf("\n\n\n %s won the election.", Data[0].names);

	else
	{
		voteDifference = Data[0].votes - Data[1].votes;
		int CoalitionVotes;
		printf("\n\n\n");

		if (x == IndirectPresidental || x == DirectPresidental)
		{

			if (uncountedVotes == 0)
			{
				if ( (x == DirectPresidental && Percent1 > 50)
					|| x == IndirectPresidental && (wonElectors1 > totalElectors/2) )
					printf(" %s won the election.", Data[0].names);
				else
					printf(" There is no winner.");
			}

			else if ((totalVotes / 2) > uncountedVotes + Data[0].votes)
				printf(" No one will win the election.");

			else if ((totalVotes / 2) < uncountedVotes + Data[0].votes && uncountedVotes < (totalVotes / 2))
			{
				if (Data[0].votes > totalVotes / 2)
					printf(" %s will definitely win election.", Data[0].names);

				else
					printf(" %s is closer to winning the election than the other candidates.", Data[0].names);
			}

			else printf(" The winner is not definite...");
			
		}
		else if (x == Parliamentary)
		{
			if (uncountedVotes == 0)
			{
				if (Percent1 > 50)
					printf(" %s won the majority.", Data[0].names);

				else
				{
					CoalitionVotes = 0;
					printf(" The possible coalition is: ");
					for (int i = 0; ; i++)
					{
						printf("%s", Data[i].names);
						CoalitionVotes += Data[i].votes;

						if (CoalitionVotes > totalVotes / 2)
							break;

						printf("-");
					}
				}
			}
			else if (voteDifference > uncountedVotes)
			{
				printf(" The vote difference between '%s' and '%s': %d", Data[0].names, Data[1].names, voteDifference);
				printf("\n %s will definitely win the election.", Data[0].names);

				if (Data[0].votes + uncountedVotes <= (totalVotes / 2))
				{
					printf(", but not the majority.");

					CoalitionVotes = 0;
					printf("\n The possible coalition is: ");
					for (int i = 0; ; i++)
					{
						printf(Data[i].names);
						CoalitionVotes += Data[i].votes;

						if (CoalitionVotes > totalVotes / 2)
							break;

						printf("-");
					}
				}

				else if (Data[0].votes + uncountedVotes > (totalVotes / 2))
					printf(" and can guarantee the majority.");

				else printf(" and the majority.");
			}
			else printf(" The winner is not definite...");
		}
		else
		{
			if (uncountedVotes == 0 && voteDifference > 0)
				printf(" The %s votes won the referendum.", Data[0].names);

			else if (uncountedVotes < voteDifference)
			{
				printf(" The vote difference between '%s' and '%s': %d", Data[0].names, Data[1].names, voteDifference);
				printf("\n The %s votes will definitely win the referendum.", Data[0].names);
			}

			else printf(" Hard to tell which one will win.");
		}
	}

	printf("\n\n (R)Retry\n (E)Exit");
	free(Data);
}