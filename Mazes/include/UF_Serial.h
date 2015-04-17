#ifndef UF_SERIAL_H
#define UF_SERIAL_H

#include "UF_ADT.h"
/*
 * Written By Bryce Summers on 4/12/2015.
 *
 * Purpose : This is a standard serial implementation of a Union Find Data structure.
 *
 */

class UF_Serial : public UF_ADT
{
    public:
        UF_Serial(int size);
        ~UF_Serial();

        void op_union(EdgeList edgeList);
        void op_union(int v1, int v2);
        int op_find(int vertex);


        bool connected(int v1, int v2);

    protected:
    private:

        // Links two root elements.
        void link(int v1, int v2);
};

#endif // UF_SERIAL_H
