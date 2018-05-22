#include "stdafx.h"
#include "MST_SUCCESSOR.h"
#include "SP_Successor.h"
#include <fstream>
#include <iostream>
#include <string>


void SP_Successor::display() //displays the neighbour list
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

void SP_Successor::load(std::string name) // loads structure from the file name - name of the file
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

void SP_Successor::solveDikstra(int v, int res) // solves shortest path using dijkstra algorithm v- starting vertex res-end vertex
{
	costTab = new int[vNum];//arry of costs
	prevTab = new int[vNum]; //array of previous vertices
	QS = new bool[vNum];//array of visited vertices
	stack = new int[vNum];//stack used for printing
	stPointer = 0;//pointer to the stack

	for (int i = 0; i < vNum; i++) //sets starting conditions 
	{
		costTab[i] = MAXINT;
		prevTab[i] = -1;
		QS[i] = false;
	}

	costTab[v] = 0; //sets cost of the start point to 0

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

	for (int i = 0; i < vNum; i++)
	{
		std::cout << i << ": ";


		for (int j = i; j > -1; j = prevTab[j]) stack[stPointer++] = j;

		//display the path, loading vertices from the stack

		while (stPointer) std::cout << stack[--stPointer] << " ";

		// at the end of the path we display the cost

		std::cout << "$" << costTab[i] << std::endl;
	}
	//cost of the end vertex
	std::cout << " !!!Wynik wyszukiwania koszt: " << costTab[res] << std::endl;
	return;
}

void SP_Successor::solveFordBellman(int v, int res)
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

	if (bf(v,costTab,prevTab))
	{
		stack = new int[vNum];              // simple stack
		stPointer = 0;

		for (int i = 0; i < vNum; i++)
		{
			std::cout << i << ": ";
			for (int j = i; j != -1; j = prevTab[j]) //put the vertices of the path on the stack
				stack[stPointer++] = j;            // in order from last to first

			while (stPointer)                 // print vertices from the stack
				std::cout << stack[--stPointer] << " "; // in order from first to last

			std::cout << "$" << costTab[i] << std::endl; // at the end display the cost of the path
		}
		delete[] stack;                  // delete the stack
	}
	else std::cout << "Negative Cycle found!" << std::endl;
	//cost of the end vertex
	std::cout << " !!!Wynik wyszukiwania koszt: " << costTab[res] << std::endl;

}

bool SP_Successor::bf(int v, int*costTab, int*prevTab)// v- start vertex
{
	
	bool test;
	TNode * temp;

	costTab[v] = 0;                       // set cost of the start vertex to 0
	for (int i = 1; i < vNum; i++)          // relaxing loop
	{
		test = true;                  // means there is no change in costTab and prevTab
		for (int x = 0; x < vNum; x++)        // search through vertices
			for (temp = A[x]; temp; temp = temp->next) // seach neighbor list for x vertex
				if (costTab[temp->v] > costTab[x] + temp->weight) // check if the condition of the relaxation is true
				{
					test = false;           // means there is a change in costTab and prevTab
					costTab[temp->v] = costTab[x] + temp->weight; // relax edge from x to the neighbor
					prevTab[temp->v] = x;           // predeccessor of neighbor is set to x
				}
		if (test) return true;         // if there was no change we stop
	}

	// chceck if there is a negative cycle

	for (int i = 0; i < vNum; i++)
		for (temp = A[i]; temp; temp = temp->next)
			if (costTab[temp->v] > costTab[i] + temp->weight) return false; // there is a negative cycle

	return true;
}

void SP_Successor::addEdge(int s, int e, int w)// adds edge to the neighbour list s- starting point e-end point w- weight of the connection
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
