#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<pair<int, int>> matrixToEdgeList(vector<vector<int>>& matrix) 
{
    vector<pair<int, int>> edges;

    for (int i = 0; i < matrix.size(); ++i) 
    {
        for (int j = i + 1; j < matrix[i].size(); ++j) 
        {
            if (matrix[i][j] == 1) 
            {
                edges.push_back({ i + 1, j + 1 }); 
            }
        }
    }

    return edges;
}

void ReadMatrixAndPrintEdgeList()
{
    int n; 
    ifstream inputFile("input_matrix.txt"); 

    if (!inputFile.is_open()) 
    {
        cerr << "The file could not be opened for reading" << endl;
        return;
    }

    inputFile >> n;
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            inputFile >> adjacencyMatrix[i][j];
        }
    }

    inputFile.close();

    vector<pair<int, int>> edgeList = matrixToEdgeList(adjacencyMatrix);

    cout << "List of graph edges:" << endl;
    for (const auto& edge : edgeList) 
    {
        cout << edge.first << " -- " << edge.second << endl;
    }
}

vector<vector<int>> edgeListToMatrix(vector<vector<int>>& edges, int n) 
{
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));

    for (const auto& edge : edges) 
    {
        int u = edge[0] - 1;
        int v = edge[1] - 1;
        int weight = edge[2];

        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight; 
    }

    return adjacencyMatrix;
}

void ReadEdgeListAndPrintMatrix()
{
    int n, m; 
    ifstream inputFile("input_edges.txt"); 

    if (!inputFile.is_open()) 
    {
        cerr << "The file could not be opened for reading" << endl;
        return;
    }

    inputFile >> n >> m; 

    vector<vector<int>> edges; 

    int u, v, weight;
    for (int i = 0; i < m; ++i) 
    {
        inputFile >> u >> v >> weight;
        edges.push_back({ u, v, weight });
    }

    inputFile.close(); 

    vector<vector<int>> adjacencyMatrix = edgeListToMatrix(edges, n);

    cout << "Adjacency matrix:" << endl;
    for (const auto& row : adjacencyMatrix) 
    {
        for (int val : row) 
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    
    ReadEdgeListAndPrintMatrix();
    ReadMatrixAndPrintEdgeList();
    return 0;

}