#include "../include/UF_ADT.h"


UF_ADT::UF_ADT()
{

}

UF_ADT::~UF_ADT()
{

}

// Naive implementation.
void UF_ADT::op_union(EdgeList edgeList)
{
    std::vector<int> v1 = edgeList.vertex1;
    std::vector<int> v2 = edgeList.vertex2;
    int len = edgeList.vertex1.size();

    for(int i = 0; i < len; i++)
    {
        op_union(v1[i], v2[i]);
    }
}

/* Resizes the F structure to the given size.
 * and disassociates all of the sets.
 */
 /*
void UF_ADT::makeSize(int size)
{

    free(this->parents);
    free(this->ranks);

    this->parents = (int*) malloc(sizeof(int)*size);
    this->ranks   = (int*) malloc(sizeof(int)*size);
    this->size = size;

    for(int i = 0; i < size; i++)
    {
        parents[i] = i;
        ranks[i]   = 0;
    }

}
*/

