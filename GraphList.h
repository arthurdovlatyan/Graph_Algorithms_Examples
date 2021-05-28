//
// Created by arthurdovlat on 5/27/21.
//

#ifndef GRAPH_GRAPHLIST_H
#define GRAPH_GRAPHLIST_H
#include "Graph.h"
#include <vector>
#include <list>

class GraphList : public Graph {
private:

    /*
     * Struct representing a node
     */
    struct Nodes{
        int val,cost;
        bool operator<(const int n) {
            return val < n;
        }
        bool operator==(const int n) {
            return val == n;
        }
    };
    static const int adjacent = 0;
    void DFSHelper(int v,std::vector<bool>& visitedNodes,std::vector<int>& path);
    /*
     * A vector of lists of nodes representing the adjacency list
     */
    std::vector<std::list<Nodes>> adjList;
public:
    /*
     * Default Constructor
     */
    GraphList(int numOfNodes);

    GraphList(GraphDirectnessType DirType,GraphWeightedType WeightType, int numOfNodes);

    void addEdge(int v, int w, int weight = 0) override;

    std::vector<int> BFS(int v,int to = 0) override;

    std::vector<int> DFS(int v) override;

    void printGraph() override;

    int returnCost(int v,int w) override;

    void componentsHelper(int v,std::vector<bool>& visitedNodes,std::vector<int>& components,int count);

    std::vector<int> findConnectedComponents() override;

    ~GraphList() override;
};


#endif //GRAPH_GRAPHLIST_H
