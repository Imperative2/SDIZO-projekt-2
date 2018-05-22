#pragma once
#include <string>
class SP_Matrix
{
	int vNum; //number of vertices
	int edgeNum; //number of edges
	int** matrix; // pointer to matrix

	int *costTab; // array of costs
	int *prevTab; // array of previous vertices
	int *stack; // stack
	int stPointer; // pointer to the stack
	bool *QS; // array of visited vertices



public:
	const int MAXINT = 2147483647; // maximum size of int being used as infinity
	void display(); //display the matrix
	void load(std::string name);// loads structure from the file name - name of the file
	void solveDikstra(int v, int res);// solves shortest path using dijkstra algorithm v- starting vertex res-end vertex
	void solveFordBellman(int v, int res);// solves shortest path using ford-bellman algorithm v- starting vertex res-end vertex
	bool bf(int v, int* costTab, int* prevTab);
	void addEdge(int s, int e, int w, int i); // adds edge to the neighbour list s- starting point e-end point w- weight of the connection
	SP_Matrix();//constructor
	~SP_Matrix();//destructor
};

