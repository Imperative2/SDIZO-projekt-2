#pragma once
#include <string>

struct TNode //representation of the node of the graph
{
	TNode * next = NULL; //pointer to the next Tnode
	int v; //end point vertex
	int weight; //weight of the connection
};
class MST_SUCCESSOR
{
private:
	int cost;//cost of the whole graph
	int vNum;//number of the vertices
	TNode ** A;//pointer to the neighbor list
	int edgeNum;//number of the edges
public:
	void dipsay();//displays the neighbor list
	void load(std::string);//loads structure from the file name - name of the file
	void addEdge(int s, int e, int w);//adds edge to the graph s - start point vertex e - endpoint vertex w- weight of the connection
	TNode* getAList(int n);//returns list of the neighbors for the given vertex

	MST_SUCCESSOR* solvePRIM();// solves and creates minimum spaing tree for the graph using prime algorithm
	MST_SUCCESSOR* solveKRUSKAL();//not used
	MST_SUCCESSOR* sK();// solves and creates minimum spaing tree for the graph using kruskal algorithm

	bool check(int* m);//chceck if all elements of the array are the same color m- array containing colors(int)
	void changeCol(int *m, int org, int dest);//changes color of destination group to the color of the original group


	MST_SUCCESSOR();
	MST_SUCCESSOR(int n);
	~MST_SUCCESSOR();
};

