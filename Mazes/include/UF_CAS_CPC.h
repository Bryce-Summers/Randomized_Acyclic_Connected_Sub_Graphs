#ifndef UF_CAS_CPC_H
#define UF_CAS_CPC_H


/* Union Find, Compare and Swap based lock free, Constrained Path compression.
 *
 */

class UF_CAS_CPC  : public UF_ADT
{
    public:
        UF_CAS_CPC();
        virtual ~UF_CAS_CPC();

        void op_union(EdgeList edgeList);
        bool op_union(int v1, int v2);
        int op_find(int vertex);


        bool connected(int v1, int v2);

    protected:
    private:
};

#endif // UF_CAS_CPC_H
