#ifndef UF_CAS_NPC_H
#define UF_CAS_NPC_H


class UF_CAS_NPC : public UF_ADT
{
    public:
        UF_CAS_NPC(int size);
        virtual ~UF_CAS_NPC();

        // This is implemented naively in ADT at the moment. */
        // void op_union(EdgeList edgeList);
        bool op_union(int v1, int v2);
        int op_find(int vertex);

        bool connected(int v1, int v2);

    protected:
    private:

        // The Data.
        int * parents;
        int * ranks;
        int size;
};

#endif // UF_CAS_NPC_H
