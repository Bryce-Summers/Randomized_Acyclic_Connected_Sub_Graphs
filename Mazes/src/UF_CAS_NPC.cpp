#include "../include/UF_CAS_NPC.h"
#include <stdlib.h>
#include <stdexcept>
#include <algorithm>
#include <atomic>

/*
 * Lock Free Union Find structure with no path compression.
 *
 * By Bryce Summers, 4/20/2015.
 *
 * Invariants : the parent of every node n is <= than n.
 */

UF_CAS_NPC::UF_CAS_NPC(int size)
{
    this->size = size;
    this->uf_arr = (uf_cas_npc_node_t*) malloc (sizeof(uf_cas_npc_node_t) * size);
    if (this->uf_arr == NULL)
    {
        throw std::runtime_error("Malloc failed in initializing UF");
    }

    for(int i = 0; i < size; i++)
    {
        this->uf_arr[i].parent = i;
    }
}

UF_CAS_NPC::~UF_CAS_NPC()
{
    free (this->uf_arr);
}


bool UF_CAS_NPC::connected(int v1, int v2)
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
    } while (root1 != this->uf_arr[root1].parent
          || root2 != this->uf_arr[root2].parent);



    return false;
}

bool UF_CAS_NPC::op_union(int v1, int v2)
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


int UF_CAS_NPC::op_find(int vertex_initial)
{
    // 1st transversal, find the root.

    int vertex = vertex_initial;
    int parent = this->uf_arr[vertex].parent ;

    while(parent != vertex)
    {
        vertex = parent;
        parent = this->uf_arr[vertex].parent;
    }

    int root = vertex;
    return root;
}

// Link greater to lesser.
//@assert v2 > v1
bool UF_CAS_NPC::link(int v1, int v2)
{
    // If already linked or incorrect ordering
    if (v2 <= v1) {
        return false;
    }

    // Do precheck to see if we dont have to do
    // costly CAS
    if (this->uf_arr[v2].parent != v2) {
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
    bool result = __sync_bool_compare_and_swap(&this->uf_arr[v2].parent, v2, v1);
    if (result == true)
    {
        _mm_sfence();
    }
    return result;
}
