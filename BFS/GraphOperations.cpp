#include "GraphOperations.h"

void breadthFirstSearch(const std::vector<std::vector<int>>& adjacencyMatrix, int startVertex, std::vector<bool>& visited)
{
    std::queue<int> bfsQueue;
    bfsQueue.push(startVertex);
    visited[startVertex] = true;

    std::cout << "Breadth-First Search starting from vertex " << startVertex + 1 << " : ";

    while (!bfsQueue.empty())
    {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();
        std::cout << currentVertex + 1 << " ";

        for (const auto& neighbor : adjacencyMatrix[currentVertex])
        {
            if (!visited[neighbor])
            {
                bfsQueue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    std::cout << std::endl;
}

bool readGraph(const std::string& fileName, std::vector<Edge>& edges, int& numVertices, int& numEdges, int& startVertex)
{
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file. Exiting...\n";
        return false;
    }

    inputFile >> numVertices >> numEdges;

    if (numVertices <= 0)
    {
        std::cerr << "Invalid number of vertices. Exiting...\n";
        return false;
    }

    edges.reserve(numEdges);
    for (int i = 0; i < numEdges; ++i)
    {
        int vertex1, vertex2, cost;
        inputFile >> vertex1 >> vertex2 >> cost;
        if (vertex1 < 1 || vertex1 > numVertices || vertex2 < 1 || vertex2 > numVertices)
        {
            std::cerr << "Invalid vertex in edge. Exiting...\n";
            return false;
        }
        edges.emplace_back(Edge{ vertex1 - 1, vertex2 - 1, cost });
    }

    inputFile >> startVertex;
    if (startVertex < 1 || startVertex > numVertices)
    {
        std::cerr << "Invalid start vertex. Exiting...\n";
        return false;
    }

    inputFile.close();
    return true;
}

std::vector<std::vector<int>> createAdjacencyMatrix(const std::vector<Edge>& edges, int numVertices)
{
    std::vector<std::vector<int>> adjacencyMatrix(numVertices);

    for (const auto& edge : edges)
    {
        adjacencyMatrix[edge.vertex1].push_back(edge.vertex2);
        adjacencyMatrix[edge.vertex2].push_back(edge.vertex1);
    }

    return adjacencyMatrix;
}
