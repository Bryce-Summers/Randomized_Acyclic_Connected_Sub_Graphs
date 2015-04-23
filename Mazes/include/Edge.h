#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <functional>


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

namespace std
{
		template <>
		struct hash<Edge>
		{
		  size_t operator()(const Edge& e) const
		  {
            size_t hash_1 = std::hash<int>()(e.vertex_1);
            //size_t hash_2 = std::hash<size_t>()(std::hash<int>()(e.vertex_2));

            // h(h(v1) ^ h(h(v2)))
            //return std::hash<size_t>()(hash_1 ^ hash_2);

            //Merkle–Damgard_construction like
            // h(h(v1) ^ v2)
            return std::hash<size_t>()(hash_1 ^ e.vertex_2);
		  }
		};
}


#endif // EDGE_H
