#include <iostream>
#include "GraphOperations.h"

int main()
{
    std::vector<Edge> edges;
    int numVertices, numEdges;

    if (!readGraph("graph.txt", edges, numVertices, numEdges))
    {
        return 1;
    }

    std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix(edges, numVertices);

    std::vector<std::vector<int>> components;
    findConnectedComponents(adjacencyMatrix, components);

    std::cout << "Connected Components:\n";
    for (const auto& component : components)
    {
        for (int vertex : component)
        {
            std::cout << vertex + 1 << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
