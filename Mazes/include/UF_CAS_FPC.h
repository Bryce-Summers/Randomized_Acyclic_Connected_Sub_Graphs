#ifndef UF_CAS_FPC_H
#define UF_CAS_FPC_H

/*
 * Union Find, Compare and Swap based lock free, Full Path compression.
 * Written by Bryce Summers on 4/19/2015.
 *
 * This implementation is non blocking and is lock free.
 */

class UF_CAS_FPC  : public UF_ADT
{
    public:
        UF_CAS_FPC();
        virtual ~UF_CAS_FPC();

        // This is implemented naively in ADT at the moment. */
        //void op_union(EdgeList edgeList);
        bool op_union(int v1, int v2);
        int op_find(int vertex);

        bool connected(int v1, int v2);

    protected:
    private:
};

#endif // UF_CAS_FPC_H
