// SDIZO_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MST_SUCCESSOR.h"
#include "MST_MATRIX.h"
#include "PQUEUE.h"
#include "SP_Successor.h"
#include "SP_Matrix.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <String>
#include <time.h>
#include <cmath>
#include<iomanip>


double PCFreq = 0.0;
__int64 CounterStart = 0;

int test_p = 100; //liczba określająca ilość testów
int rG = 1000; //liczba okreslacjaca zakres rand()


void startCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double getCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}



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
					int edgeProcentage;
					int vNum;
					int edgeNum;

					std::cout << "\npodaj ilosc wierzcholkow: ";
					std::cin >> vNum;
					std::cout << "\npodaj procent zageszczenia krawedzi :";
					std::cin >> edgeProcentage;

					edgeNum = (int) ((vNum * vNum*(edgeProcentage / 100)) + vNum);

					org = new MST_SUCCESSOR(vNum);
					morg = new MST_MATRIX(vNum, edgeNum);

					int columnIndexer = 0;

					for (int i = 0; i < vNum; i++)
					{
						int rng = rand() % 20 + 1;
						org->addEdge(i, (i + 1) % vNum, rng);
						morg->addEdge(i, (i + 1) % vNum, rng, columnIndexer);
						columnIndexer++;
					}

					for (int i = 0; i < edgeNum-vNum; i++)
					{
						int rng = rand() % 20 + 1;
						int a = rand() % vNum;
						int b = rand() % vNum;
						if (a == b) a = (a*2 + 1) % vNum;
						org->addEdge(a, b, rng);
						morg->addEdge(a , b , rng, columnIndexer);
						columnIndexer++;
					}
					break;

				}
				case 3:
				{
					std::cout << "\n\n\n\n\n";
					morg->display();
					org->dipsay();
					break;
				}
				case 4:
				{
					std::cout << "\n\n\n\n\n";
					res = org->solvePRIM();
					res->dipsay();
					mres = morg->solvePrim();
					mres->display();
					break;
				}
				case 5:
				{
					std::cout << "\n\n\n\n\n";
					res =  org->sK();
					res->dipsay();
					mres = morg->solveKRUSKAL();
					mres->display();

					//delete res;
					//delete mres;
			
					break;
				}
				case 6:
				{
					delete org;
					delete morg;

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
				std::cout << "\n\n\n\n\n";

				org->display();
				morg->display();
				break;
			}
			case 4:
			{
				std::cout << "\n\n\n\n\n";
				int s, e;
				std::cout << "podaj wierzcholek poczatkowy: ";
				std::cin >> s;
				std::cout << "\npodaj wierzcholek koncowy: ";
				std::cin >> e;
				std::cout << std::endl;
				std::cout << "lista:" << std::endl;
				org->solveDikstra(s,e);
				std::cout << "macierz:" << std::endl;
				morg->solveDikstra(s, e);
				break;
			}
			case 5:
			{
				std::cout << "\n\n\n\n\n";
				int s, e;
				std::cout << "podaj wierzcholek poczatkowy: ";
				std::cin >> s;
				std::cout << "\npodaj wierzcholek koncowy: ";
				std::cin >> e;
				std::cout << std::endl;
				std::cout << "lista:" << std::endl;
				org->solveFordBellman(s,e);
				std::cout << "macierz:" << std::endl;
				morg->solveFordBellman(s, e);

				break;
			}
			case 6:
			{
				delete org;
				delete morg;
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
	srand(time(NULL));

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

