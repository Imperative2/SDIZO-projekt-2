#pragma once
#include <string>

struct TNode
{
	TNode * next;
	int v;
	int weight;
};
class MST_SUCCESSOR
{
private:
	int cost;
	int vNum;
	TNode ** A;
	int edgeNum;
public:
	void dipsay();
	void load(std::string);
	void addEdge(int s, int e, int w);
	TNode* getAList(int n);

	MST_SUCCESSOR* solvePRIM();
	MST_SUCCESSOR* solveKRUSKAL();


	MST_SUCCESSOR();
	MST_SUCCESSOR(int n);
	~MST_SUCCESSOR();
};

