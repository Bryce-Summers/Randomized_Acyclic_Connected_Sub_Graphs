#include "../include/UF_CAS_NPC.h"
#include <stdlib.h>
/*
 * Lock Free Union Find structure with no path compression.
 *
 * By Bryce Summers, 4/20/2015.
 *
 * Invariants : the parent of every node n is <= than n.
 */

UF_CAS_NPC::UF_CAS_NPC(int size)
{
    this->parents = (int*) malloc(sizeof(int)*size);
    this->ranks   = (int*) malloc(sizeof(int)*size);
    this->size = size;

    for(int i = 0; i < size; i++)
    {
        parents[i] = i;
        ranks[i]   = 0;
    }
}

UF_CAS_NPC::~UF_CAS_NPC()
{
    free(parents);
    free(ranks);
}


bool UF_CAS_NPC::connected(int v1, int v2)
{
    // FIXME
    return op_find(v1) == op_find(v2);
}

bool UF_CAS_NPC::op_union(int v1, int v2)
{
    // FIXME.

    link(op_find(v1), op_find(v2));
    return true;
}


int UF_CAS_NPC::op_find(int vertex_initial)
{
    // 1st transversal, find the root.

    int vertex = vertex_initial;

    int parent = parents[vertex];

    while(parent != vertex)
    {
        vertex = parent;
        parent = parents[vertex];
    }

    int root = vertex;
    return root;

    // No Path compression.
}

// Link greater to lesser.
void UF_CAS_NPC::link(int v1, int v2)
{
    // Compare and Swap goes here.
}
