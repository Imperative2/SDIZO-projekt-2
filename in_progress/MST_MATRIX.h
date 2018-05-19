#pragma once
#include<iostream>
class MST_MATRIX
{
private:

	int** matrix;
	int cost;
	int vNum;
	int edgeNum;

public:
	void addEdge(int s,int e,int w);
	void display();
	void load(std::string name);
	MST_MATRIX solvePrim();
	MST_MATRIX solveKRUSKAL();
	MST_MATRIX();
	~MST_MATRIX();
};

