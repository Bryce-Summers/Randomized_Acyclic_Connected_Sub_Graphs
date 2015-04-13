#ifndef EDGE_H
#define EDGE_H


class Edge
{
    public:
        Edge(int v1, int v2);
        virtual ~Edge();

        int vertex_1;
        int vertex_2;

    protected:
    private:
};

#endif // EDGE_H
