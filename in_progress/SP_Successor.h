#pragma once
#include <string>
class SP_Successor
{
private:
	int vNum;
	TNode** A;
	int edgeNum;

	int *costTab;
	int *prevTab;
	int *stack;
	int stPointer;
	bool *QS;



public:
	const int MAXINT = 2147483647;
	void display();
	void load(std::string name);
	void solveDikstra(int v,int res);
	void solveFordBellman();
	void addEdge(int s, int e, int w);
	SP_Successor();
	~SP_Successor();
};

