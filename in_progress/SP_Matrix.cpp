#include "stdafx.h"
#include "MST_SUCCESSOR.h"
#include "SP_Matrix.h"
#include <iostream>
#include <fstream>
#include <iomanip>


void SP_Matrix::display()
{
	for (int i = 0; i < vNum; i++)
	{
		std::cout << "vertex " << i << ": ";
		for (int j = 0; j < edgeNum; j++)
		{
			std::cout << std::setw(5);
			std::cout << std::setfill(' ');
			if (matrix[i][j] != 0)
				std::cout << matrix[i][j] / std::abs(matrix[i][j]);
			else
				std::cout << "0 ";
		}
		std::cout << std::endl;
	}
}

void SP_Matrix::load(std::string name)
{
	name += ".txt";
	std::ifstream file;
	file.open(name);
	if (file.is_open())
	{
		file >> edgeNum;
		file >> vNum;


		matrix = new int*[vNum];
		for (int i = 0; i < edgeNum; i++)
		{
			matrix[i] = new int[edgeNum];
		}
		for (int i = 0; i < vNum; i++)
		{
			for (int j = 0; j < edgeNum; j++)
			{
				matrix[i][j] = 0;
			}
		}


		int s, e, w;
		for (int i = 0; i < edgeNum; i++)
		{

			file >> s;
			file >> e;
			file >> w;
			addEdge(s, e, w, i);
		}


		std::cout << "done!!!" << std::endl;
	}
	else
	{
		std::cout << "Error!!!" << std::endl;
	}

	system("pause");
}

void SP_Matrix::solveDikstra(int v, int res)
{
	costTab = new int[vNum];
	prevTab = new int[vNum];
	QS = new bool[vNum];
	stack = new int[vNum];
	stPointer = 0;

	TNode * temp;

	TNode **graf = new TNode*[vNum*2];

	for (int i = 0; i < vNum; i++)
	{
		costTab[i] = MAXINT;
		prevTab[i] = -1;
		QS[i] = false;
	}

	costTab[v] = 0;

	for (int i = 0; i < vNum; i++)
	{
		for (int j = 0; j < edgeNum; j++)
		{
			if (matrix[i][j] > 0)
			{
				int k;
				for (int l = 0; l < vNum; l++)
				{
					if (matrix[l][j] < 0) k = l;
				}
				TNode *tstart = new TNode;             // Tworzymy element listy s¹siedztwa
				tstart->v = k;                    // Wierzcho³ek docelowy krawêdzi
				tstart->weight = matrix[i][j];                    // Waga krawêdzi
				tstart->next = graf[i];
				graf[i] = tstart;
			}
		}
	}

	for (int i = 0; i < vNum; i++)
	{
		int j, u;
		for (j = 0; QS[j]; j++);
		for (u = j++; j < vNum; j++)
		{
			if (!QS[j] && (costTab[j] < costTab[u]))
				u = j;
		}

		QS[u] = true;


		for (temp = graf[u]; temp; temp = temp->next)
		{

			if (!QS[temp->v] && (costTab[temp->v] > costTab[u] + temp->weight))
			{
				costTab[temp->v] = costTab[u] + temp->weight;
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

void SP_Matrix::addEdge(int s, int e, int w, int column)
{
	matrix[s][column] = w;
	matrix[e][column] = -w;
}

SP_Matrix::SP_Matrix()
{
}


SP_Matrix::~SP_Matrix()
{
}
