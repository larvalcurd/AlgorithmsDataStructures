#include "GraphOperations.h"

void depthFirstSearch(const std::vector<std::vector<int>>& adjacencyMatrix, int startVertex, std::vector<bool>& visited, std::vector<int>& component)
{
    std::stack<int> dfsStack;
    dfsStack.push(startVertex);
    visited[startVertex] = true;

    while (!dfsStack.empty())
    {
        int currentVertex = dfsStack.top();
        dfsStack.pop();
        component.push_back(currentVertex);

        for (const auto& neighbor : adjacencyMatrix[currentVertex])
        {
            if (!visited[neighbor])
            {
                dfsStack.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

void findConnectedComponents(const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<std::vector<int>>& components)
{
    int numVertices = adjacencyMatrix.size();
    std::vector<bool> visited(numVertices, false);

    for (int i = 0; i < numVertices; ++i)
    {
        if (!visited[i])
        {
            std::vector<int> component;
            depthFirstSearch(adjacencyMatrix, i, visited, component);
            components.push_back(component);
        }
    }
}

bool readGraph(const std::string& fileName, std::vector<Edge>& edges, int& numVertices, int& numEdges)
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
