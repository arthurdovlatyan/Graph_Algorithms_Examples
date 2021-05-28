//
// Created by arthurdovlat on 5/27/21.
//

#ifndef GRAPH_GRAPHMATRIX_H
#define GRAPH_GRAPHMATRIX_H

#include "Graph.h"
#include <vector>

class GraphMatrix : public Graph {
private:
    static const int adjacent = 1;
    void DFSHelper(int v,std::vector<bool>& visitedNodes,std::vector<int>& path);
    std::vector<std::vector<int>> adjMatrix;
public:
    GraphMatrix(int numOfNodes);

    GraphMatrix(GraphDirectnessType DirType,GraphWeightedType WeightType, int numOfNodes);

    void addEdge(int v, int w, int weight) override;

    std::vector<int> BFS(int v,int to = -1) override;

    std::vector<int> DFS(int v) override;

    void printGraph() override;

    int returnCost(int v,int w) override;

    void componentsHelper(int v,std::vector<bool>& visitedNodes,std::vector<int>& components,int count);

    std::vector<int> findConnectedComponents() override;

    ~GraphMatrix() override;
};


#endif //GRAPH_GRAPHMATRIX_H
