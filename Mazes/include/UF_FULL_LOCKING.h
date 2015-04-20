#ifndef UF_FULL_LOCKING_H
#define UF_FULL_LOCKING_H

/*
 * Full locking implementation of a Union Find Structure.
 *
 * The synchronization is done on a global level.
 *
 * Written by Bryce Summers on 4/19/2015.
 */

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

        // Links two root elements.
        void link(int v1, int v2);

        // Global full data structure locks.
        // No concurrency.
        void lock_all();
        void unlock_all();

    std::mutex lock_all;

};

#endif // UF_FULL_LOCKING_H
