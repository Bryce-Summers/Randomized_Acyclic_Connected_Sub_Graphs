#include "../include/UF_CAS_FPC.h"

/*
 * Lock Free Union Find Structure Implementation.
 *
 * Written by Bryce Summers on 4/19/2015.
 *
 * Guarantees : The results of an op_find will be valid as of the time the call is initiated.
 *              The returned representative node may be out of date by the time is is returned to the user.
 *
 * Calls to Union are guaranteed to always larger integers to smaller integers.
 *
 * Would using an alternative total ordering improve cache behavior?
 */

UF_CAS_FPC::UF_CAS_FPC(int size) : UF_ADT()
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

UF_CAS_FPC::~UF_CAS_FPC()
{
    free(parents);
    free(ranks);
}


// FIXME : Implement this function iff we want to parrellelize it.
/*
void UF_CAS_FPC::op_union(EdgeList edgeList)
{

}
*/

bool UF_CAS_FPC::op_union(int v1, int v2)
{
    return false;
}

/*
 * Finds are mostly read operations with path compression.
 * We will need to consider the implications of write traffic.
 * We might want to perform tests to make sure a pointer needs to be changed before doing naive writes.
 */
int UF_CAS_FPC::op_find(int vertex_initial)
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


    // Second transversal, path compression.

    vertex = vertex_initial;
    parent = parents[vertex];

    while(parent != vertex)
    {
        parents[vertex] = root;
        vertex = parent;
        parent = parents[vertex];
    }

    return root;
}


bool UF_CAS_FPC::connected(int v1, int v2)
{
    int root1 = op_find(v1);
    int root2 = op_find(v2);

    // FIXME Handle degeneracies.

    return parents[root1] == parents[root2];

}
