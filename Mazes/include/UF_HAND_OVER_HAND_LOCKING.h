#ifndef UF_HAND_OVER_HAND_LOCKING_H
#define UF_HAND_OVER_HAND_LOCKING_H


class UF_HAND_OVER_HAND_LOCKING  : public UF_ADT
{
    public:
        UF_HAND_OVER_HAND_LOCKING();
        virtual ~UF_HAND_OVER_HAND_LOCKING();

        void op_union(EdgeList edgeList);
        void op_union(int v1, int v2);
        int op_find(int vertex);


        bool connected(int v1, int v2);

    protected:
    private:
};

#endif // UF_HAND_OVER_HAND_LOCKING_H
