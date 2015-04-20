#ifndef UF_HAND_OVER_HAND_LOCKING_H
#define UF_HAND_OVER_HAND_LOCKING_H


/*
 * Per Node locks implementation.
 * This implementation allows synchronization at the node level.
 *
 * Written By Bryce Summers on 4/19/2015.
 *
 */


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

        std::mutex * locks; // Mutexes for every element.

        void lock(int vert);
        void unlock(int vert);
};

#endif // UF_HAND_OVER_HAND_LOCKING_H
