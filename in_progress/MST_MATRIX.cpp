#include "stdafx.h"
#include "MST_SUCCESSOR.h"
#include "MST_MATRIX.h"
#include"PQUEUE.h"
#include <iostream>
#include<fstream>
#include<cmath>
#include<iomanip>

//dodawanie wierzcho³ka do grafu s- pocz¹tek e- koniec  w-waga  column - nr. krawedzi
//add vertex to the graph s- start point e- end point w -weight of the connection column - nb. of the edge
void MST_MATRIX::addEdge(int s, int e, int w, int column)
{
	matrix[s][column] = w;
	matrix[e][column] = -w;
	cost += w;
}
//display the matrix
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
//loads structure from the file name - name of the file
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
MST_MATRIX* MST_MATRIX::solvePrim()// solves and creates minimum spaing tree for the graph using prime algorithm
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

	for (int i = 0; i < vNum - 1; i++) // adds edges to the graph
	{
		for (int j = 0; j < edgeNum; j++) //adds all edges to the queue of available connections
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
			e = Q.getFront();// load best connection from the queue
			Q.pop();//pops the edge from the queue
		} while (visited[e.v2] == true);// chcecks if the edge leads to the visited vertex

		T->addEdge(e.v1, e.v2, e.weight, columnNum);// we add the edge to the graph
		columnNum++;//we increase iterator
		visited[e.v2] = true;// sets endpoint vertex as visited
		startV = e.v2;
	}

	return T;
}

MST_MATRIX* MST_MATRIX::solveKRUSKAL()// solves and creates minimum spaing tree for the graph using kruskal algorithm
{
	TNode * temp;
	PQUEUE Q(edgeNum*2);
	Edge e; //edge
	MST_MATRIX * T = new MST_MATRIX(vNum,edgeNum);

	int *colorTab = new int[vNum];//creates different color sets for all vertices
	for (int i = 0; i < vNum; i++)
	{
		colorTab[i] = i;
	}

	int startV;

	Q.display();
	std::cout << "\n\n\n";
	for (int i = 0; i < vNum; i++)// adds all edges to the priority queue
	
	{
		for (int j = 0; j < edgeNum; j++)
		{
			int a;//weight
			int b;//pointing to
			if (matrix[i][j] > 0)
			{
				for (int l = 0; l < vNum; l++)
				{
					if (matrix[l][j] < 0)
					{
						a = matrix[i][j];
						b = l;
					}
				}
				e.v1 = i;
				e.v2 = b;
				e.weight = a;
				Q.push(e);
			}
		}
	}

	//Q.display();
	int columnIndexer = 0;
	do {

		e = Q.getFront();//gets best edge from the queue
		Q.pop();//pops the edge
		if (colorTab[e.v1] != colorTab[e.v2])//we check if the two vertices belong to the different color set
		{
			T->addEdge(e.v1, e.v2, e.weight,columnIndexer);//add edge to the result graph
			changeCol(colorTab, colorTab[e.v1], colorTab[e.v2]);//we merge both sets
			columnIndexer++;
		}

	} while (check(colorTab) == false);//checks if all colors belong to the same set

	return T;
}

bool MST_MATRIX::check(int * tab)//checks if all colors belong to the same set
{
	int a = tab[0];
	for (int i = 0; i < vNum; i++)
	{
		if (a != tab[i])
		{
			return false;
		}
	}
	return true;
}

void MST_MATRIX::changeCol(int * tab, int org, int dest) // sets color of the destination set to that of the original set
{
	for (int i = 0; i < vNum; i++)
	{
		if (tab[i] == dest)
		{
			tab[i] = org;
		}
	}
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
