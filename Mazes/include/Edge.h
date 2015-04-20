#ifndef EDGE_H
#define EDGE_H

class Edge
{
    public:
        Edge(int v1, int v2);
        virtual ~Edge();

        int vertex_1;
        int vertex_2;

        bool operator> (Edge other) const
        {
            if (vertex_1 > other.vertex_1)
            {
                return true;
            }
            else if (vertex_1 == other.vertex_1)
            {
                return vertex_2 > other.vertex_2;
            }
            else
            {
                return false;
            }
        }


        bool operator< (Edge other) const
        {
            if (vertex_1 < other.vertex_1)
            {
                return true;
            }
            else if (vertex_1 == other.vertex_1)
            {
                return vertex_2 < other.vertex_2;
            }
            else
            {
                return false;
            }
        }

        bool operator== (Edge other) const
        {
            return vertex_1==other.vertex_1
                && vertex_2==other.vertex_2;
        }

    protected:
    private:
};

#endif // EDGE_H
