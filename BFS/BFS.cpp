#include <iostream>
#include "GraphOperations.h"

int main()
{
    std::vector<Edge> edges;
    int numVertices, numEdges, startVertex;

    if (!readGraph("graph.txt", edges, numVertices, numEdges, startVertex))
    {
        return 1;
    }

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix(edges, numVertices);

    std::vector<bool> visited(numVertices, false);
    breadthFirstSearch(adjacencyMatrix, startVertex - 1, visited);

    return 0;
}
