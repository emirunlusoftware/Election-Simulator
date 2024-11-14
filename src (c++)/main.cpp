#include <iostream>
#include <conio.h>
#include "main.h"
using namespace std;

int main() {
	char Option;

	while(1)
	{
		system("cls");
		MainMenu();

		while(1)
		{
			Option = _getch();
			switch (Option)
			{
				case '1': Election(IndirectPresidental); break;
				case '2': Election(DirectPresidental); break;
				case '3': Election(Parliamentary); break;
				case '4': Election(Referendum); break;

				case 'E':
				case 'e':
					return 0;

				default : continue;
			}

			while (1)
			{
				Option = _getch();

				if (Option == 'r' || Option == 'R')
					break;
				else if (Option == 'e' || Option == 'E')
					return 0;
			}
			break;
		}
	}
}