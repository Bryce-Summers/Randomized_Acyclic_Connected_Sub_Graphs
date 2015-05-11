#ifndef UF_CAS_CPC_H
#define UF_CAS_CPC_H

#include "UF.h"

/* Union Find, Compare and Swap based lock free, Constrained Path compression.
 *
 */

typedef struct {
        int parent;
} uf_cas_cpc_node_t;

class UF_CAS_CPC  : public UF_ADT
{
    public:
        UF_CAS_CPC(int size, int k);
        virtual ~UF_CAS_CPC();

        //void op_union(EdgeList edgeList);
        bool op_union(int v1, int v2);
        int op_find(int vertex);


        bool connected(int v1, int v2);

    protected:
    private:

        // The Data.
        uf_cas_cpc_node_t *nodes;
        int k;
        int size;
        bool link(int vertex1, int vertex2);
        void path_compression(int vertex, int root);
};

#endif // UF_CAS_CPC_H
