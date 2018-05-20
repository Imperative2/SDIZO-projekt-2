#include "stdafx.h"
#include "PQUEUE.h"
#include "DSStruct.h"
#include "MST_SUCCESSOR.h"
#include <iostream>
#include <string>
#include <fstream>


void MST_SUCCESSOR::dipsay()
{
	for (int i = 0; i < vNum; i++)
	{
		std::cout << "vertex " << i << "  : ";
		TNode * temp = A[i];
		while (temp)
		{
			std::cout << temp->v << ":" << temp->weight<<"    ";
			temp = temp->next;

		}
		std::cout << std::endl;
	}

	std::cout << "\n Whole tree weight: " << cost<<std::endl;
}

void MST_SUCCESSOR::load(std::string name)
{
	name += ".txt";
	std::ifstream file;
	file.open(name);
	if (file.is_open())
	{
		file >> edgeNum;
		file >> vNum;


		A = new TNode *[vNum];

		for (int i = 0; i < vNum; i++)
		{
			A[i] = NULL;
		}

		int s, e, w;
		for (int i = 0; i < edgeNum; i++)
		{

			file >> s;
			file >> e;
			file >> w;
			addEdge(s, e, w);
		}


		std::cout << "done!!!" << std::endl;
	}
	else
	{
		std::cout << "Error!!!" << std::endl;
	}

	system("pause");

}

void MST_SUCCESSOR::addEdge(int s, int e, int w)
{
	TNode *temp = A[s];
	while (true)
	{
		if (temp == NULL)
		{
			cost += w;


			TNode *tstart = new TNode;
			tstart->v = e;
			tstart->weight = w;
			tstart->next = A[s];
			A[s] = tstart;

			TNode *tend = new TNode;
			tend->v = s;
			tend->weight = w;
			tend->next = A[e];
			A[e] = tend;
			
			break;
		}
		else
			temp = temp->next;

	}
}

TNode * MST_SUCCESSOR::getAList(int n)
{
	return A[n];
}

MST_SUCCESSOR* MST_SUCCESSOR::solvePRIM()
{

	PQUEUE Q(edgeNum*2);
	Edge e;
	MST_SUCCESSOR * T = new MST_SUCCESSOR(vNum);
	bool * visited = new bool[vNum];


	for (int i = 0; i < vNum; i++)
	{
		visited[i] = false;
	}

	int startV = 0;
	TNode * temp;
	visited[0] = true;
	for (int i = 0; i < vNum-1; i++)          // Do drzewa dodamy n - 1 krawêdzi grafu
	{

		temp = A[startV];
		while (temp != NULL)
		{
			if (visited[temp->v] == false)
			{
				e.v1 = startV;
				e.v2 = temp->v;
				e.weight = temp->weight;
				Q.push(e);
			}
			temp = temp->next;
		}
		Q.display();
		do
		{
			e = Q.getFront();              // Pobieramy krawêdŸ z kolejki
			Q.pop();
		} while (visited[e.v2]);       // KrawêdŸ prowadzi poza drzewo?

		T->addEdge(e.v1,e.v2,e.weight);                 // Dodajemy krawêdŸ do drzewa rozpinaj¹cego
		visited[e.v2] = true;         // Oznaczamy drugi wierzcho³ek jako odwiedzony
		startV = e.v2;
	}


	return T;
}

MST_SUCCESSOR * MST_SUCCESSOR::solveKRUSKAL()
{
	TNode * temp;
	PQUEUE Q(edgeNum);
	Edge e;
	MST_SUCCESSOR * T = new MST_SUCCESSOR(vNum);
	

	DSStruct Z(vNum);                  // Struktura zbiorów roz³¹cznych

	for (int i = 0; i < vNum; i++)
		Z.MakeSet(i);                 // Dla ka¿dego wierzcho³ka tworzymy osobny zbiór

	for (int i = 0; i < vNum; i++)
	{
		for (temp = A[i]; temp != NULL; temp = temp->next)
		{
			e.v1 = i;                 // to tworzymy krawêdŸ
			e.v2 = temp->v;
			e.weight = temp->weight;
			Q.push(e);
		}
	}
	
	for (int i = 1; i < vNum; i++)          // Pêtla wykonuje siê n - 1 razy !!!
	{
		do
		{
			e = Q.getFront();              // Pobieramy z kolejki krawêdŸ
			Q.pop();                    // KrawêdŸ usuwamy z kolejki
		} while (Z.FindSet(e.v1) == Z.FindSet(e.v2));
		T->addEdge(e.v1, e.v2, e.weight);                // Dodajemy krawêdŸ do drzewa
		Z.UnionSets(e);               // Zbiory z wierzcho³kami ³¹czymy ze sob¹
	}

	
	MST_SUCCESSOR * P = T;
	return T;
}



MST_SUCCESSOR::MST_SUCCESSOR()
{
	vNum = 0;
	cost = 0;
}

MST_SUCCESSOR::MST_SUCCESSOR(int n)
{
	A = new TNode *[n];            // Tworzymy tablicê dynamiczn¹
	for (int i = 0; i < n; i++) A[i] = NULL; // i wype³niamy j¹ pustymi listami
	vNum = n ;                   // Zapamiêtujemy d³ugoœæ tablicy
	cost = 0;
}


MST_SUCCESSOR::~MST_SUCCESSOR()
{
	TNode *temp;
	TNode *r;

	for (int i = 0; i < vNum; i++)
	{
		temp = A[i];
		while (temp)
		{
			r = temp;                      // Zapamiêtujemy wskazanie
			temp = temp->next;                // Przesuwamy siê do nastêpnego elementu listy
			delete r;                   // Usuwamy element
		}
	}

	delete[] A;
}
