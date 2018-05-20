#pragma once
#include <string>
class SP_Matrix
{
	int vNum;
	int edgeNum;
	int** matrix;

	int *costTab;
	int *prevTab;
	int *stack;
	int stPointer;
	bool *QS;



public:
	const int MAXINT = 2147483647;
	void display();
	void load(std::string name);
	void solveDikstra(int v, int res);
	void solveFordBellman();
	void addEdge(int s, int e, int w, int i);
	SP_Matrix();
	~SP_Matrix();
};

