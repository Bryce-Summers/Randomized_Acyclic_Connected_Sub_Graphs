#ifndef UF_FULL_LOCKING_H
#define UF_FULL_LOCKING_H


class UF_FULL_LOCKING  : public UF_ADT
{
    public:
        UF_FULL_LOCKING();
        virtual ~UF_FULL_LOCKING();


        void op_union(EdgeList edgeList);
        void op_union(int v1, int v2);
        int op_find(int vertex);


        bool connected(int v1, int v2);


    protected:
    private:
};

#endif // UF_FULL_LOCKING_H
