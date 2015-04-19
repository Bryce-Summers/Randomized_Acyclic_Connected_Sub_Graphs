#ifndef UF_ADT_H
#define UF_ADT_H

#include "Graph.h"
/*
 * Written by Bryce Summers on 4/12/2015.
 *
 * This class defines the abstract data type of a Union Find structure.
 *
 * These structures will support operations on fixed contiguous integer valued indices.
 * The interpretation of the results of these union and find operations will be left to the code utilizing the structure.
 */

class UF_ADT
{
    public:
        UF_ADT(int sizes);
        virtual ~UF_ADT() = 0;

        virtual void op_union(EdgeList edgeList) = 0;
        virtual void op_union(int v1, int v2) = 0;

        // Guaranteed to be valid for sequential implementations.
        // For concurrent usage using comparison checks, please use connected instead.
        virtual int op_find(int vertex) = 0;

        virtual bool connected (int v1, int v2) = 0;

        // The Data.
        int * parents;
        int * ranks;
        int size;

    protected:
    private:
};

#endif // UF_STRUCTURE_H
