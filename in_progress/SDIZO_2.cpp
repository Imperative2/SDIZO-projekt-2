// SDIZO_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MST_SUCCESSOR.h"
#include "MST_MATRIX.h"
#include "PQUEUE.h"
#include <iostream>



void menuMST()
{
	MST_SUCCESSOR *org = new MST_SUCCESSOR();
	MST_SUCCESSOR *res;
	MST_MATRIX *morg = new MST_MATRIX();
	MST_MATRIX *mres;


	while (true)
	{
		std::cout << " 1. Wczytaj z pliku." << std::endl;
		std::cout << " 2. Losuj graf." << std::endl;
		std::cout << " 3. Wyswietl graf listowo i macierzowo." << std::endl;
		std::cout << " 4. Algorytm Prima listowo i macierzowo." << std::endl;
		std::cout << " 5. Algorytm Kruskala listowo i macierzowo." << std::endl;
		std::cout << " 6. Exit." << std::endl;

		int a;
		std::cin >> a;

			switch (a)
			{
				case 1:
				{
					std::cout << "podaj nazwe pliku ";
					std::string name;
					std::cin >> name;
					org->load(name);
					morg->load(name);

					break;
				}
				case 2:
				{
					break;

				}
				case 3:
				{
					morg->display();
					org->dipsay();
					break;
				}
				case 4:
				{
					res = org->solvePRIM();
					res->dipsay();
					break;
				}
				case 5:
				{
					res = org->solveKRUSKAL();
					res->dipsay();
					break;
					break;
				}
				case 6:
				{
					return;
				}
				default:
				{
					std::cout << "error! TRY AGAIN!" << std::endl;
					break;
				}
			}
	}
}

int main()
{
	while (true)
	{
		std::cout << " 1. MST Algorytm Prima || Kruskala" << std::endl;
		std::cout << " 2. SP Algorytm Dikstry  || Forda-Bellmana." << std::endl;
		std::cout << " 3. MF Algorytm Forda-Fulkersona" << std::endl;
		std::cout << " 4. Exit" << std::endl;

		int a;
		std::cin >> a;

		switch (a)
		{
			case 1:
			{
				menuMST();
				break;
			}
			case 2:
			{
				break;

			}
			case 3:
			{
				break;
			}
			case 4:
			{
				return 0;
				break;
			}
			case 5:
			{
				break;
			}
			case 6:
			{
				return 0;
			}
			default:
			{
				std::cout << "error! TRY AGAIN!" << std::endl;
				break;
			}
		}
	}


}

