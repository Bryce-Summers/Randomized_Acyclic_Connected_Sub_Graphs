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
        bool op_union(int v1, int v2);
        int op_find(int vertex);


        bool connected(int v1, int v2);

    protected:
    private:

        std::mutex * locks; // Mutexes for every element.

        void lock(int vert);
        void unlock(int vert);

        // Finds the root node, locks it, then returns the value of the root node.
        // The caller is responsible for calling unlock(RETURN_VALUE) after they are done using it.
        // If this function encounters node 'stop', then  it does not take the lock and returns stop.
        // NOTE : -1 should not ever the index of any node and is used to indicate no valid stop node.
        int find_and_lock(int vert, int stop = -1);
};

#endif // UF_HAND_OVER_HAND_LOCKING_H
