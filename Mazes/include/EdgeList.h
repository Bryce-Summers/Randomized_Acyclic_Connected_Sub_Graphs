#ifndef EDGELIST_H
#define EDGELIST_H


class EdgeList
{
    public:
        EdgeList();
        virtual ~EdgeList();

        // Stores a list of vertex1, vertex2 pairs.
        std:vector<int> vertex1;
        std:vector<int> vertex2;

        // Explicit edge objects.
        std:vector<Edge> edges;


        void addEdge(int v1, int v2);

        // Randomizes the order of the edge list.
        void shuffle();

        void getSize()
        {
            return vertex1.size();
        }

    protected:
    private:
};

#endif // EDGELIST_H
