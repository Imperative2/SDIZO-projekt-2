#pragma once

struct Edge
{
	int v1;
	int v2;
	int weight;
};

class PQUEUE
{

private:
	int size;
	int hpos;
	Edge * heap;

public:
	void push(Edge e);
	void pop();
	Edge getFront();
	PQUEUE(int n);
	~PQUEUE();
};

