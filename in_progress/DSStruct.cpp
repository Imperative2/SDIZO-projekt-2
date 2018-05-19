#include "stdafx.h"
#include "PQUEUE.h"
#include "DSStruct.h"


DSStruct::DSStruct(int n)
{
	Z = new DSNode[n];             // Tworzymy tablic� dla n element�w zbior�w
}


DSStruct::~DSStruct()
{
	delete[] Z;           
}


void DSStruct::MakeSet(int v)
{
	Z[v].up = v;
	Z[v].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w kt�rym jest wierzcho�ek v
int DSStruct::FindSet(int v)
{
	if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
	return Z[v].up;
}

// Polaczenie ze soba zbioru v i u
void DSStruct::UnionSets(Edge e)
{
	int ru, rv;

	ru = FindSet(e.v1);	// korze� drzewa z w�z�em u
	rv = FindSet(e.v2);             //  korze� drzewa z w�z�em v
	if (ru != rv)                    // Korzenie musz� by� r�ne
	{
		if (Z[ru].rank > Z[rv].rank)   // Por�wnujemy rangi drzew
			Z[rv].up = ru;              // ru wi�ksze, do��czamy rv
		else
		{
			Z[ru].up = rv;              // r�wne lub rv wi�ksze, do��czamy ru
			if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
		}
	}
}