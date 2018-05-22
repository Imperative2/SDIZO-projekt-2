#pragma once
#include<iostream>
#include<string>
class MST_MATRIX
{
private:



	int** matrix;//pointer to the matrix
	int cost;//cost of the whole graph
	int vNum;//number of the vertices
	int edgeNum;//number of the edges

public:
	void addEdge(int s,int e,int w,int column);//adds edge to the graph s - start point vertex e - endpoint vertex w- weight of the connection
	void display();//displays the matrix
	void load(std::string name);//loads structure from the file name - name of the file
	MST_MATRIX* solvePrim();// solves and creates minimum spaing tree for the graph using prime algorithm
	MST_MATRIX* solveKRUSKAL();// solves and creates minimum spaing tree for the graph using kruskal algorithm

	bool check(int *tab);//chceck if all elements of the array are the same color m- array containing colors(int)
	void changeCol(int *tab, int org, int dest);//changes color of destination group to the color of the original group
	MST_MATRIX();
	MST_MATRIX(int v, int e);
	~MST_MATRIX();
};

