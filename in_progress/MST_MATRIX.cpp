#include "stdafx.h"
#include "MST_MATRIX.h"
#include <iostream>
#include<fstream>
#include<cmath>
#include<iomanip>


void MST_MATRIX::addEdge(int s, int e, int w)
{
	matrix[s][e] = w;
	matrix[e][s] = -w;
	cost += w;
}

void MST_MATRIX::display()
{
	for (int i = 0; i < vNum; i++)
	{
		std::cout << "vertex " << i << ": ";
		for (int j = 0; j < edgeNum; j++)
		{
			std::cout << std::setw(3);
			if (matrix[i][j] != 0)
				std::cout << matrix[i][j] / std::abs(matrix[i][j]) << "  ";
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

MST_MATRIX MST_MATRIX::solvePrim()
{
	return MST_MATRIX();
}

MST_MATRIX MST_MATRIX::solveKRUSKAL()
{
	return MST_MATRIX();
}

MST_MATRIX::MST_MATRIX()
{
}


MST_MATRIX::~MST_MATRIX()
{
}
