#ifndef UF_HAND_OVER_HAND_LOCKING_H
#define UF_HAND_OVER_HAND_LOCKING_H

#include "UF.h"

/*
 * Per Node locks implementation.
 * This implementation allows synchronization at the node level.
 *
 * Written By Bryce Summers on 4/19/2015.
 *
 * All locks taken in descending order. lock(2) before lock(1).
 *
 * We cannot maintain locks on the root nodes, because that may cause deadlock.
 */

typedef struct{

        int parent;
        std::mutex lock; // Every node has a mutex.

} uf_hand_over_hand_node_t;

class UF_HAND_OVER_HAND_LOCKING  : public UF_ADT
{
    public:
        UF_HAND_OVER_HAND_LOCKING(int size);
        virtual ~UF_HAND_OVER_HAND_LOCKING();

		/* -- Public Interface Methods.
		 *
		 * None of these methods keep locks.
		 */

		/* Returns true iff the sets containing v1 and v2 were disconnected
		 * and have now been connected.
		 */
        bool op_union(int v1, int v2);

		// finds the current root node of this vertex.
		// Does not keep any locks.
        int op_find(int vertex);

		// true --> nodes are connected as of the ending of this call.
		// false -> nodes were disconnected at the time of beginning of the call.
        bool connected(int v1, int v2);

    protected:
    private:

        // The Data.

        int size;
		uf_hand_over_hand_node_t * nodes;

        void lock(int vert);
        void unlock(int vert);

		// Returns true if the link went through.
        bool link (int v1, int v2);
};

#endif // UF_HAND_OVER_HAND_LOCKING_H
