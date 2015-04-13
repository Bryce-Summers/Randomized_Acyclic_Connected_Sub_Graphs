#ifndef UF_SERIAL_H
#define UF_SERIAL_H

/*
 * Written By Bryce Summers on 4/12/2015.
 *
 * Purpose : This is a standard serial implementation of a Union Find Data structure.
 *
 */

class UF_Serial : UF_ADT
{
    public:
        UF_Serial();
        virtual ~UF_Serial();

        virtual void op_union(EdgeList edgeList);
        virtual void op_union(int v1, int v2);
        virtual int op_find(int vertex);

    protected:
    private:

        // Links two root elements.
        void link(int v1, int v2);
};

#endif // UF_SERIAL_H
