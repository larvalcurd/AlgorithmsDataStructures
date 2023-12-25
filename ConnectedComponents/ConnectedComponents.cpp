#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

struct Edge
{
    int vertex1;
    int vertex2;
    int cost;
};

void depthFirstSearch(const vector<vector<int>>& adjacencyMatrix, int startVertex, vector<bool>& visited, vector<int>& component)
{
    stack<int> dfsStack;
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

void findConnectedComponents(const vector<vector<int>>& adjacencyMatrix, vector<vector<int>>& components)
{
    int numVertices = adjacencyMatrix.size();
    vector<bool> visited(numVertices, false);

    for (int i = 0; i < numVertices; ++i)
    {
        if (!visited[i])
        {
            vector<int> component;
            depthFirstSearch(adjacencyMatrix, i, visited, component);
            components.push_back(component);
        }
    }
}

bool readGraph(const string& fileName, vector<Edge>& edges, int& numVertices, int& numEdges)
{
    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "Error opening the file. Exiting...\n";
        return false;
    }

    inputFile >> numVertices >> numEdges;

    if (numVertices <= 0)
    {
        cerr << "Invalid number of vertices. Exiting...\n";
        return false;
    }

    edges.reserve(numEdges);
    for (int i = 0; i < numEdges; ++i)
    {
        int vertex1, vertex2, cost;
        inputFile >> vertex1 >> vertex2 >> cost;
        if (vertex1 < 1 || vertex1 > numVertices || vertex2 < 1 || vertex2 > numVertices)
        {
            cerr << "Invalid vertex in edge. Exiting...\n";
            return false;
        }
        edges.emplace_back(Edge{ vertex1 - 1, vertex2 - 1, cost });
    }

    inputFile.close();
    return true;
}

vector<vector<int>> createAdjacencyMatrix(const vector<Edge>& edges, int numVertices)
{
    vector<vector<int>> adjacencyMatrix(numVertices);

    for (const auto& edge : edges)
    {
        adjacencyMatrix[edge.vertex1].push_back(edge.vertex2);
        adjacencyMatrix[edge.vertex2].push_back(edge.vertex1);
    }

    return adjacencyMatrix;
}

int main()
{
    vector<Edge> edges;
    int numVertices, numEdges;

    if (!readGraph("graph.txt", edges, numVertices, numEdges))
    {
        return 1;
    }

    vector<vector<int>> adjacencyMatrix = createAdjacencyMatrix(edges, numVertices);

    vector<vector<int>> components;
    findConnectedComponents(adjacencyMatrix, components);

    cout << "Connected Components:\n";
    for (const auto& component : components)
    {
        for (int vertex : component)
        {
            cout << vertex + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
