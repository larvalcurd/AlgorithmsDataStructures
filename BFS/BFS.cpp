#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Edge 
{
    int vertex1;
    int vertex2;
    int cost;
};

void breadthFirstSearch(const vector<vector<int>>& adjacencyMatrix, int startVertex, vector<bool>& visited) 
{
    queue<int> bfsQueue;
    bfsQueue.push(startVertex);
    visited[startVertex] = true;

    cout << "Breadth-First Search starting from vertex " << startVertex + 1 << " : ";

    while (!bfsQueue.empty()) 
    {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();
        cout << currentVertex + 1 << " ";

        for (const auto& neighbor : adjacencyMatrix[currentVertex]) 
        {
            if (!visited[neighbor]) 
            {
                bfsQueue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    cout << endl;
}

bool readGraph(const string& fileName, vector<Edge>& edges, int& numVertices, int& numEdges, int& startVertex) 
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

    inputFile >> startVertex;
    if (startVertex < 1 || startVertex > numVertices) 
    {
        cerr << "Invalid start vertex. Exiting...\n";
        return false;
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
    int numVertices, numEdges, startVertex;

    if (!readGraph("graph.txt", edges, numVertices, numEdges, startVertex)) 
    {
        return 1;
    }

    vector<vector<int>> adjacencyMatrix = createAdjacencyMatrix(edges, numVertices);

    vector<bool> visited(numVertices, false);
    breadthFirstSearch(adjacencyMatrix, startVertex - 1, visited);

    return 0;
}
