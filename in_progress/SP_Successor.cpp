#include "stdafx.h"
#include "MST_SUCCESSOR.h"
#include "SP_Successor.h"
#include <fstream>
#include <iostream>
#include <string>


void SP_Successor::display()
{
	for (int i = 0; i < vNum; i++)
	{
		std::cout << "vertex " << i << "  : ";
		TNode * temp = A[i];
		while (temp)
		{
			std::cout << temp->v << ":" << temp->weight << "    ";
			temp = temp->next;

		}
		std::cout << std::endl;
	}

}

void SP_Successor::load(std::string name)
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

void SP_Successor::solveDikstra(int v, int res)
{
	costTab = new int[vNum];
	prevTab = new int[vNum];
	QS = new bool[vNum];
	stack = new int[vNum];
	stPointer = 0;

	for (int i = 0; i < vNum; i++)
	{
		costTab[i] = MAXINT;
		prevTab[i] = -1;
		QS[i] = false;
	}

	costTab[v] = 0;

	for (int i = 0; i < vNum; i++)
	{
		int j, u;
		for (j = 0; QS[j]; j++);
		for ( u = j++; j < vNum; j++)
		{
			if (!QS[j] && (costTab[j] < costTab[u]))
				u = j;
		}

		QS[u] = true;

		TNode *temp;

		for (temp = A[u]; temp ; temp = temp->next)
		{

			if (!QS[temp->v] && (costTab[temp->v] > costTab[u] + temp->weight))
			{
				costTab[temp->v] = costTab[u]  + temp->weight;
				prevTab[temp->v] = u;
			}
		}
	}
	//for (int i = 0; i < vNum; i++)
	//{
	//	std::cout << "i " << i << " koszt: " << costTab[i] << " prevTab: " << prevTab[i] << std::endl;
	//}

	for (int i = 0; i < vNum; i++)
	{
		std::cout << i << ": ";

		// Œcie¿kê przechodzimy od koñca ku pocz¹tkowi,
		// Zapisuj¹c na stosie kolejne wierzcho³ki

		for (int j = i; j > -1; j = prevTab[j]) stack[stPointer++] = j;

		// Wyœwietlamy œcie¿kê, pobieraj¹c wierzcho³ki ze stosu

		while (stPointer) std::cout << stack[--stPointer] << " ";

		// Na koñcu œcie¿ki wypisujemy jej koszt

		std::cout << "$" << costTab[i] << std::endl;
	}

	std::cout << " !!!Wynik wyszukiwania koszt: " << costTab[res] << std::endl;
	return;
}

void SP_Successor::addEdge(int s, int e, int w)
{
	TNode *temp = A[s];
	while (true)
	{
		if (temp == NULL)
		{
			

			TNode *tstart = new TNode;
			tstart->v = e;
			tstart->weight = w;
			tstart->next = A[s];
			A[s] = tstart;
			break;
		}
		else
			temp = temp->next;

	}
}

SP_Successor::SP_Successor()
{
	vNum = 0;
	A = NULL;
}


SP_Successor::~SP_Successor()
{
}
