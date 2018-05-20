#include "stdafx.h"
#include "MST_MATRIX.h"
#include"PQUEUE.h"
#include <iostream>
#include<fstream>
#include<cmath>
#include<iomanip>


void MST_MATRIX::addEdge(int s, int e, int w, int column)
{
	matrix[s][column] = w;
	matrix[e][column] = -w;
	cost += w;
}

void MST_MATRIX::display()
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
	std::cout << std::endl;
	std::cout << "\n Whole tree weight: " << cost << std::endl;
}

void MST_MATRIX::load(std::string name)
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

MST_MATRIX* MST_MATRIX::solvePrim()
{
	PQUEUE Q(edgeNum*2);
	MST_MATRIX *T = new MST_MATRIX(vNum, edgeNum);
	Edge e;
	bool * visited = new bool[vNum];
	for (int i = 0; i < vNum; i++)
	{
		visited[i] = false;
	}

	int columnNum = 0;
	int startV = 0;

	visited[0] = true;

	for (int i = 0; i < vNum - 1; i++)
	{
		for (int j = 0; j < edgeNum; j++)
		{
			if (matrix[startV][j] > 0)
			{
				int k;
				for (int l = 0; l < vNum; l++)
				{
					if (matrix[l][j] < 0)
						k = l;
				}

				if (visited[k] == false)
				{
					e.v1 = startV;
					e.v2 = k;
					e.weight = matrix[startV][j];
					Q.push(e);
					
				}
			}
			else if (matrix[startV][j] < 0)
			{
				int k;
				for (int l = 0; l < vNum; l++)
				{
					if (matrix[l][j] > 0)
						k = l;
				}

				if (visited[k] == false)
				{
					e.v1 = startV;
					e.v2 = k;
					e.weight = matrix[k][j];
					Q.push(e);

				}
			}
		}
		do
		{
			e = Q.getFront();
			Q.pop();
		} while (visited[e.v2] == true);

		T->addEdge(e.v1, e.v2, e.weight, columnNum);
		columnNum++;
		visited[e.v2] = true;
		startV = e.v2;
	}

	return T;
}

MST_MATRIX MST_MATRIX::solveKRUSKAL()
{
	return MST_MATRIX();
}

MST_MATRIX::MST_MATRIX()
{
	cost = 0;
	vNum = 0;
	edgeNum = 0;
}

MST_MATRIX::MST_MATRIX(int v, int e)
{
	vNum = v;
	edgeNum = e;
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
}


MST_MATRIX::~MST_MATRIX()
{
	for (int i = 0; i < vNum; i++)
	{
		delete[] matrix[i];
	}
	cost = 0;
	vNum = 0;
	edgeNum = 0;
	delete[] matrix;
}
