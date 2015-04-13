#include "UF_Serial.h"

UF_Serial::UF_Serial(int size)
{
    parents = (int*) malloc(sizeof(int)*size);
    ranks   = (int*) malloc(sizeof(int)*size);
    this.size = size;

    for(int i = 0; i < size; i++)
    {
        parents[i] = i;
        ranks[i]   = 0;
    }
}

UF_Serial::~UF_Serial()
{
    free(parents);
    free(ranks);
}

void UF_Serial::op_union(EdgeList edgeList)
{
    std::vector<int> v1 = edgeList -> vertex1;
    std::vector<int> v2 = edgeList -> vertex2;
    int len = edgeList ->vertex1 ->size();

    for(int i = 0; i < len; i++)
    {
        op_union(v1[i], v2[i]);
    }
}

void UF_Serial::op_union(int v1, int v2)
{
    link(op_find(e1), op_find(e2));
}

int UF_Serial::op_find(int vertex)
{
    int parent = parents[vertex];


    if(parent != vertex)
    {
        // Recursive Find;
        parent = op_find(parent);

        // Path Compression.
        parents[vertex] = parent;
    }

    return parent;
}

// Union by Rank.
void UF_Serial::link(int v1, int v2)
{
    // Very important.
    if(v1 == v2)
	{
		return;
	}

	int rank1 = ranks[v1];
	int rank2 = ranks[v2];

	// v1 Greater depth.
	if(rank1 > rank2)
	{
		parents[v2] = v1;
		return;
	}

	// v2 Greater depth.
	else if(rank2 > rank1)
	{
		parents[v1] = v2;
		return;
	}

	// Equal depth --> increase rank.
	else
	{
	    parents[v2] = v1;
        ranks[v1] = rank1 + 1;
	}
}
