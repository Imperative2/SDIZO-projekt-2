// SDIZO_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MST_SUCCESSOR.h"
#include "MST_MATRIX.h"
#include "PQUEUE.h"
#include "SP_Successor.h"
#include "SP_Matrix.h"
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
					mres = morg->solvePrim();
					mres->display();
					break;
				}
				case 5:
				{
					res = org->solveKRUSKAL();
					res->dipsay();
			
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

void menuSP()
{
	SP_Successor * org = new SP_Successor();
	SP_Matrix *morg = new SP_Matrix();



	while (true)
	{
		std::cout << " 1. Wczytaj z pliku." << std::endl;
		std::cout << " 2. Losuj graf." << std::endl;
		std::cout << " 3. Wyswietl graf listowo i macierzowo." << std::endl;
		std::cout << " 4. Algorytm Dikstry listowo i macierzowo." << std::endl;
		std::cout << " 5. Algorytm Forda-Bellmana listowo i macierzowo." << std::endl;
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

				org->display();
				morg->display();
				break;
			}
			case 4:
			{
				int s, e;
				std::cout << "podaj wierzcholek poczatkowy: ";
				std::cin >> s;
				std::cout << "\npodaj wierzcholek koncowy: ";
				std::cin >> e;
				std::cout << std::endl;
				org->solveDikstra(s,e);
				std::cout << "macierz:" << std::endl;
				morg->solveDikstra(s, e);
				break;
			}
			case 5:
			{


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
				menuSP();
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

