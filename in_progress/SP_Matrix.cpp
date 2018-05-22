#include "stdafx.h"
#include "MST_SUCCESSOR.h"
#include "SP_Matrix.h"
#include <iostream>
#include <fstream>
#include <iomanip>


void SP_Matrix::display()//display the matrix
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

void SP_Matrix::load(std::string name)// loads structure from the file name - name of the file
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

void SP_Matrix::solveDikstra(int v, int res)// solves shortest path using dijkstra algorithm v- starting vertex res-end vertex
{
	costTab = new int[vNum];//arry of costs
	prevTab = new int[vNum];//array of previous vertices
	QS = new bool[vNum];//array of visited vertices
	stack = new int[vNum];//stack used for printingay of visited vertices
	stPointer = 0;//pointer to the stack

	TNode * temp; //temporary node

	for (int i = 0; i < vNum; i++)//sets starting conditions 
	{
		costTab[i] = MAXINT;
		prevTab[i] = -1;
		QS[i] = false;
	}

	costTab[v] = 0;//sets cost of the start point to 0

	for (int i = 0; i < vNum; i++)
	{
		int selected = v;
		bool flag = false;
		int preSelected = MAXINT;
		for (int j = 0; j < vNum; j++)
		{
			if (  QS[j] == false && costTab[j] < preSelected)
			{
				selected = j;
				preSelected = costTab[j];
			}
		}

		QS[selected] = true;
		for (int j = 0; j < edgeNum; j++) //relaxing
		{
			int a;
			int b;
			if (matrix[selected][j] > 0)
			{
				int a = 0;
				for (int l = 0; l < vNum; l++)
				{
					a = matrix[l][j];
					if (a < 0)
					{
						b = l;
						break;
					}
				}
				if (costTab[b] > costTab[selected] - a)
				{
					costTab[b] = costTab[selected] - a;
					prevTab[b] = selected;
				}
			}
		}
	}

	for (int i = 0; i < vNum; i++)
	{
		std::cout << i << ": ";

		//display the path, loading vertices from the stack

		for (int j = i; j > -1; j = prevTab[j]) stack[stPointer++] = j;

		// at the end of the path we display the cost

		while (stPointer) std::cout << stack[--stPointer] << " ";

		//cost of the end vertex

		std::cout << "$" << costTab[i] << std::endl;
	}

	std::cout << " !!!Wynik wyszukiwania koszt: " << costTab[res] << std::endl;
	return;

}

void SP_Matrix::solveFordBellman(int v, int res)
{
	costTab = new int[vNum];
	prevTab = new int[vNum];
	stack = new int[vNum];
	stPointer = 0;

	for (int i = 0; i < vNum; i++)
	{
		costTab[i] = MAXINT;
		prevTab[i] = -1;
	}

	if (bf(v, costTab, prevTab))
	{
		stack = new int[vNum];              // simple stack
		stPointer = 0;

		for (int i = 0; i < vNum; i++)
		{
			std::cout << i << ": ";
			for (int j = i; j != -1; j = prevTab[j]) //put the vertices of the path on the stack
				stack[stPointer++] = j;            // in order from last to first

			while (stPointer)                // print vertices from the stack
				std::cout << stack[--stPointer] << " "; // in order from first to last

			std::cout << "$" << costTab[i] << std::endl; // at the end display the cost of the path
		}
		delete[] stack;                  // delete the stack
	}
	else std::cout << "Negative Cycle found!" << std::endl;

	std::cout << " !!!Wynik wyszukiwania koszt: " << costTab[res] << std::endl;
}

bool SP_Matrix::bf(int v, int * costTab, int * prevTab)// v- start vertex
{

	bool test;
	TNode * temp;

	costTab[v] = 0;                       // set cost of the start vertex to 0

	for (int i = 1; i < vNum; i++)          // relaxing loop
	{
		test = true;                  // means there is no change in costTab and prevTab
		for (int x = 0; x < vNum; x++)// search through vertices
		{
			for (int j = 0; j < edgeNum; j++)// seach all edges for x vertex
			{
				if (matrix[x][j] > 0)
				{
					for (int l = 0; l < vNum; l++)
					{
						if (matrix[l][j] < 0)
						{
							if (costTab[l] > costTab[x] + matrix[x][j])// check if the condition of the relaxation is true
							{
								test = false;// means there is a change in costTab and prevTab
								costTab[l] = costTab[x] + matrix[x][j];// relax edge from x to the neighbor
								prevTab[l] = x;// predeccessor of neighbor is set to x
							}
						}
					}
				}
			}
		}
		if (test) return true;         // if there was no change we stop
	}

	


	// chceck if there is a negative cycle
	for (int x = 0; x < vNum; x++)
	{
		for (int j = 0; j < edgeNum; j++)
		{
			if (matrix[x][j] > 0)
			{
				for (int l = 0; l < vNum; l++)
				{
					if (matrix[l][j] < 0)
					{
						if (costTab[l] > costTab[x] + matrix[x][j]) return false; // there is a negative cycle
					}
				}
			}
		}
	}

	return true;
}

void SP_Matrix::addEdge(int s, int e, int w, int column)// adds edge to the neighbour list s- starting point e-end point w- weight of the connection
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
