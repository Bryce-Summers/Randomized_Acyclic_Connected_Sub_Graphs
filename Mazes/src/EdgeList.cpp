#include "../include/EdgeList.h"

EdgeList::EdgeList()
{
    //ctor
}

EdgeList::~EdgeList()
{
    //dtor
}

void EdgeList::shuffle()
{
  int len = getSize();

  if (len < 2)
  {
	  return;
  }

  // Randomly choose pairs of edges to swap.
  for(int i = 0; i < len; i++)
  {
	int index1 = rand() % (len - 1);
	int index2 = index1 + 1 + (rand() % (len - index1 - 1));

	swap(index1, index2, vertex1);
	swap(index1, index2, vertex2);

	swap(index1, index2, edges);
  }

}

void EdgeList::swap(int index1, int index2, std::vector<int>& vec)
{
  int temp = vec[index1];
  vec[index1] = vec[index2];
  vec[index2] = temp;
}

void EdgeList::swap(int index1, int index2, std::vector<Edge>& vec)
{
  Edge temp = vec[index1];
  vec[index1] = vec[index2];
  vec[index2] = temp;
}


void EdgeList::addEdge(int v1, int v2)
{
  vertex1.push_back(v1);
  vertex2.push_back(v2);

  edges.push_back(Edge(v1, v2));
}


// Splits this edge list into the input number of equal parts.
// Caller is responsible for freeing the list and all component lists.
EdgeList ** EdgeList::split(int parts)
{

  EdgeList ** output = (EdgeList **)malloc(sizeof(EdgeList*) * parts);

  int len = vertex1.size();

  for(int p = 0; p < parts; p++)
  {
	int start = len*p/parts;
	int end = len*(p+1)/parts;

	EdgeList  * output_partition = new EdgeList();
	output[p] = output_partition;

	for(int i = start; i < end; i++)
	{
	  output_partition -> addEdge(vertex1[i], vertex2[i]);
	}
  }

  return output;

}


void EdgeList::append(EdgeList * other)
{
  std::vector<int> * vertex1_other = &(other -> vertex1);
  vertex1.insert(vertex1.end(), vertex1_other->begin(), vertex1_other->end());

  std::vector<int> * vertex2_other = &(other -> vertex2);
  vertex2.insert(vertex2.end(), vertex2_other->begin(), vertex2_other->end());

  std::vector<Edge> * edges_other = &(other -> edges);
  edges.insert(edges.end(), edges_other->begin(), edges_other->end());

}


std::string EdgeList::edge_string(int index)
{
  return "(" + std::to_string(vertex1[index]) + ", " +  std::to_string(vertex2[index]) + ")\n";
}

// Returns the number of edges in this edge list.
int EdgeList::size()
{
  return vertex1.size();
}
