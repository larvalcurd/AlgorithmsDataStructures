#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

struct Edge
{
    int vertex1;
    int vertex2;
    int cost;
};

void depthFirstSearch(const std::vector<std::vector<int>>& adjacencyMatrix, int startVertex, std::vector<bool>& visited, std::vector<int>& component);

void findConnectedComponents(const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<std::vector<int>>& components);

bool readGraph(const std::string& fileName, std::vector<Edge>& edges, int& numVertices, int& numEdges);

std::vector<std::vector<int>> createAdjacencyMatrix(const std::vector<Edge>& edges, int numVertices);
