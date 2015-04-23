#include "../include/UF_CAS_CPC.h"

UF_CAS_CPC::UF_CAS_CPC(int size)
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

UF_CAS_CPC::~UF_CAS_CPC()
{
    free(parents);
    free(ranks);
}


bool UF_CAS_CPC::connected(int v1, int v2)
{
  return false;
}

bool UF_CAS_CPC:: op_union(int v1, int v2)
{

  // FIXME!!!
  return false;
}


int UF_CAS_CPC::op_find(int vertex)
{

  return vertex;


}
