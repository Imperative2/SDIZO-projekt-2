#pragma once
#include<iostream>
#include<string>
class MST_MATRIX
{
private:



	int** matrix;
	int cost;
	int vNum;
	int edgeNum;

public:
	void addEdge(int s,int e,int w,int column);
	void display();
	void load(std::string name);
	MST_MATRIX* solvePrim();
	MST_MATRIX solveKRUSKAL();
	MST_MATRIX();
	MST_MATRIX(int v, int e);
	~MST_MATRIX();
};

