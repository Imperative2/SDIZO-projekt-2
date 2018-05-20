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
	int maxSizeHeap;
	Edge * heap;

public:
	void push(Edge e);
	void pop();
	Edge getFront();
	void display();
	void bubbleUp(int index);
	void bubbleDown(int index);
	int getMaxSize() { return maxSizeHeap; };
	PQUEUE(int n);
	~PQUEUE();
};

