#include "../include/UF_CAS_CPC.h"
#include <stdlib.h>
#include <stdexcept>
#include <algorithm>
#include <atomic>

/*
 * Lock Free Union Find structure with FULL Path compression.
 *
 * By Bryce Summers, 5/10/2015
 *
 * Modifed to include path compression from NPC.
 * Invariants : the parent of every node is <= than n.
 */

UF_CAS_CPC::UF_CAS_CPC(int size, int k)
{
    this->k= k;
    this->size = size;
    this->nodes = (uf_cas_cpc_node_t*) malloc (sizeof(uf_cas_npc_node_t) * size);
    if (this->nodes == NULL)
    {
        throw std::runtime_error("Malloc failed in initializing UF");
    }

    for(int i = 0; i < size; i++)
    {
        this->nodes[i].parent = i;
    }
}

UF_CAS_CPC::~UF_CAS_CPC()
{
    free (this->nodes);
}


bool UF_CAS_CPC::connected(int v1, int v2)
{
    int tmp1, tmp2;
    int root1, root2;

    // Initialize roots
    root1 = v1;
    root2 = v2;

    do {
        root1 = op_find(root1);
        root2 = op_find(root2);

        // If roots are equal, then already unioned
        if (root1 == root2) {
            return true;
        }

        // If not try link, and if fail to link, keep
        // trying...


        // READ FENSE HERE!
        // This is required so that we can ensure that when we do
        // a read of the parent, it is not ordered before we found the
        // next root, thus creating a race
        // since it is totally possible that find(root1) will finish
        // and we will check the parent of root1 before
        // root2 is found and parent is checked. we want to check the
        // parent at a state where their roots are consistent
        _mm_lfence();
    } while (root1 != this->nodes[root1].parent
          || root2 != this->nodes[root2].parent);



    return false;
}

bool UF_CAS_CPC::op_union(int v1, int v2)
{
    int tmp1, tmp2;
    int root1, root2;

    // Initialize roots
    root1 = v1;
    root2 = v2;
    tmp1 = op_find(root1);
    tmp2 = op_find(root2);

    do  {
        tmp1 = op_find(root1);
        tmp2 = op_find(root2);
        root1 = std::min(tmp1,tmp2);
        root2 = std::max(tmp1,tmp2);

        // If roots are equal, then already unioned
        if (root1 == root2) {
            return false;
        }

        // If not try link, and if fail to link, keep
        // trying...
    } while (!link(op_find(root1), op_find(root2)));

    // If left loop, successfully linked!
    return true;
}


int UF_CAS_CPC::op_find(int vertex_initial)
{
    // 1st transversal, find the root.

    int vertex = vertex_initial;
    int parent = this->nodes[vertex].parent ;

    while(parent != vertex)
    {
        vertex = parent;
        parent = this->nodes[vertex].parent;
    }

    int root = vertex;

	path_compression(vertex_initial, root);

    return root;
}

void UF_CAS_CPC::path_compression(int vertex, int root)
{

  int i=0; // Counter for constrained path compression

  while(nodes[vertex].parent > root)
  {
	// Remember the parent.
	int parent = nodes[vertex].parent;

	// Our compression journey is no longer useful, because we have descended below the root.
	if(parent >= root)
	{
	  return;
	}

    if (i % this->k == 0) {
        // Compress the parent.
        bool result = __sync_bool_compare_and_swap(&this->nodes[vertex].parent, parent, root);

        // Forward progress on our journey down the path.
        if(result)
        {
          i++;
          vertex = parent;
        }
    } else {
        i++;
        vertex = parent;
    }
  }

  return;
}

// Link greater to lesser.
//@assert v2 > v1
bool UF_CAS_CPC::link(int v1, int v2)
{
    // If already linked or incorrect ordering
    if (v2 <= v1) {
        return false;
    }

    // Do precheck to see if we dont have to do
    // costly CAS
    if (this->nodes[v2].parent != v2) {
        return false;
    }

    // Synchronous operation doesn't require fence
    /***
     * In most cases, these builtins are considered a full barrier.
     * That is, no memory operand will be moved across the operation,
     * either forward or backward. Further, instructions will be issued as
     * necessary to prevent the processor from speculating loads across the
     * operation and from queuing stores after the operation.
     ***/
    bool result = __sync_bool_compare_and_swap(&this->nodes[v2].parent, v2, v1);
    if (result == true)
    {
        _mm_sfence();
    }
    return result;
}
