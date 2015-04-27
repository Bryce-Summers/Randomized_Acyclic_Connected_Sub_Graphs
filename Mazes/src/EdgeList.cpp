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
  }


}

void EdgeList::swap(int index1, int index2, std::vector<int>& vec)
{
  int temp = vec[index1];
  vec[index1] = vec[index2];
  vec[index2] = temp;
}

void EdgeList::addEdge(int v1, int v2)
{
  vertex1.push_back(v1);
  vertex2.push_back(v2);
}
