#include "stdafx.h"
#include "PQUEUE.h"
#include "DSStruct.h"
#include "MST_SUCCESSOR.h"
#include <iostream>
#include <string>
#include <fstream>


void MST_SUCCESSOR::dipsay()//displays the neighbor list
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

	std::cout << "\n Whole tree weight: " << cost << std::endl;
}

void MST_SUCCESSOR::load(std::string name)//loads structure from the file name - name of the file
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

void MST_SUCCESSOR::addEdge(int s, int e, int w)//adds edge to the graph s - start point vertex e - endpoint vertex w- weight of the connection
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

TNode * MST_SUCCESSOR::getAList(int n)//returns list of the neighbors for the given vertex
{
	return A[n];
}

MST_SUCCESSOR* MST_SUCCESSOR::solvePRIM()// solves and creates minimum spaing tree for the graph using prime algorithm
{

	PQUEUE Q(edgeNum * 2);
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
	for (int i = 0; i < vNum - 1; i++)          // we add n-1 edges to the graph
	{

		temp = A[startV];
		while (temp != NULL) //adds all edges to the queue of available connections
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
		//Q.display();
		do
		{
			e = Q.getFront();              // load best connection from the queue
			Q.pop();					//pops the edge from the queue
		} while (visited[e.v2]);       // chcecks if the edge leads to the visited vertex

		T->addEdge(e.v1, e.v2, e.weight);                 // we add the edge to the graph
		visited[e.v2] = true;         // sets endpoint vertex as visited
		startV = e.v2;
	}


	return T;
}
//not used
MST_SUCCESSOR * MST_SUCCESSOR::solveKRUSKAL()
{
	TNode * temp;
	PQUEUE* Q = new PQUEUE(edgeNum * 2);
	Edge e;
	MST_SUCCESSOR * T = new MST_SUCCESSOR(vNum);

	int *colorTab = new int[vNum];
	for (int i = 0; i < vNum; i++)
	{
		colorTab[i] = i;
	}

	int startV;

	for (int i = 0; i < vNum; i++)
	{
		temp = A[i];
		while (temp != NULL)
		{
			e.v1 = i;
			e.v2 = temp->v;
			e.weight = temp->weight;
			Q->push(e);

			temp = temp->next;
		}
	}

	Q->display();

	int i = 0;

	//MST_SUCCESSOR * P = T;
	//return T;
	return NULL;
}

MST_SUCCESSOR * MST_SUCCESSOR::sK()// solves and creates minimum spaing tree for the graph using kruskal algorithm
{
	TNode * temp;
	PQUEUE Q(edgeNum * 2);
	Edge e;
	MST_SUCCESSOR * T = new MST_SUCCESSOR(vNum);

	int *colorTab = new int[vNum]; //creates different color sets for all vertices
	for (int i = 0; i < vNum; i++)
	{
		colorTab[i] = i;
	}

	int startV;

	for (int i = 0; i < vNum; i++)// adds all edges to the priority queue
	{
		temp = A[i];
		while (temp != NULL)
		{
			e.v1 = i;
			e.v2 = temp->v;
			e.weight = temp->weight;
			Q.push(e);

			temp = temp->next;
		}
	}

	do {

		e = Q.getFront();//gets best edge from the queue
		Q.pop();//pops the edge
		if (colorTab[e.v1] != colorTab[e.v2])//we check if the two vertices belong to the different color set
		{
			T->addEdge(e.v1, e.v2, e.weight);//add edge to the result graph
			changeCol(colorTab, colorTab[e.v1], colorTab[e.v2]);//we merge both sets
		}

	} while (check(colorTab) == false);//checks if all colors belong to the same set

	return T;

}

bool MST_SUCCESSOR::check(int* m)//checks if all colors belong to the same set
{
	int a = m[0];
	for (int i = 0; i < vNum; i++)
	{
		if (a != m[i])
		{
			return false;
		}
	}
	return true;

}

void MST_SUCCESSOR::changeCol(int * tab, int org, int dest) // sets color of the destination set to that of the original set
{
	for (int i = 0; i < vNum; i++)
	{
		if (tab[i] == dest)
		{
			tab[i] = org;
		}
	}
}



MST_SUCCESSOR::MST_SUCCESSOR()
{
	vNum = 0;
	cost = 0;
}

MST_SUCCESSOR::MST_SUCCESSOR(int n)
{
	A = new TNode *[n];            
	for (int i = 0; i < n; i++) A[i] = NULL; 
	vNum = n;                   
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
			r = temp;                      
			temp = temp->next;               
			delete r;                  
		}
	}

	delete[] A;
}
