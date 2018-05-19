#pragma once

struct DSNode
{
	int up, rank;
};

class DSStruct
{
private:
	DSNode * Z;
public:
	DSStruct(int n);
	~DSStruct();
	void MakeSet(int v);
	int FindSet(int v);
	void UnionSets(Edge e);
};