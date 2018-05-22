#pragma once

struct Edge
{
	int v1;//starting edge
	int v2;//endpoint edge
	int weight; //weight of the connection
};

class PQUEUE
{

private:
	int size;//size of the queue
	int maxSizeHeap;//maximal size of the queue
	Edge * heap;//pointer to the heap

public:
	void push(Edge e); //adds edge to the heap
	void pop(); //pops root from the heap
	Edge getFront(); //return root of the heap
	void display(); //displays the content of the heap
	void bubbleUp(int index); //repairs heap upward
	void bubbleDown(int index);// repairs heap downward
	int getMaxSize() { return maxSizeHeap; };// return maximum size of the heap
	PQUEUE(int n); // constructor for the queue
	~PQUEUE(); // destructor for the queue
};

