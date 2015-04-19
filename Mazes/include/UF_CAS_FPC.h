#ifndef UF_CAS_FPC_H
#define UF_CAS_FPC_H

/*
 * Union Find, Compare and Swap based lock free, Full Path compression.
 * Written by Bryce Summers.
 */

class UF_CAS_FPC  : public UF_ADT
{
    public:
        UF_CAS_FPC();
        virtual ~UF_CAS_FPC();

        void op_union(EdgeList edgeList);
        void op_union(int v1, int v2);
        int op_find(int vertex);


        bool connected(int v1, int v2);

    protected:
    private:
};

#endif // UF_CAS_FPC_H
