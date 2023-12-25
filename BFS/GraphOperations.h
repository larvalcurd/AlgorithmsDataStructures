#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct Edge
{
    int vertex1;
    int vertex2;
    int cost;
};

void breadthFirstSearch(const std::vector<std::vector<int>>& adjacencyMatrix, int startVertex, std::vector<bool>& visited);

bool readGraph(const std::string& fileName, std::vector<Edge>& edges, int& numVertices, int& numEdges, int& startVertex);

std::vector<std::vector<int>> createAdjacencyMatrix(const std::vector<Edge>& edges, int numVertices);
