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
