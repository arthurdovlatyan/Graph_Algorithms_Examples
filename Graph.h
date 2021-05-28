//
// Created by arthurdovlat on 5/27/21.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include "Utility/Utility.h"
#include <iostream>
#include <vector>
#include <queue>
class Graph {
private:
    GraphDirectnessType mDirType;
    GraphWeightedType mWeightType;
    print p = print::doNotPrint;
    int MNodesNumber;
public:
    /*
     * Default Constructor
     * mDirtype = Undirected
     * mWeightType = UnWeighted
     */
    Graph();

    /*
     *
     */
    Graph(int numOfNodes);

    /*
     * Constructor taking number of nodes , DirType and WeightType
     */
    Graph(int Nodes, GraphDirectnessType DirType, GraphWeightedType WeightType);

    /*
     * Adds an edge to a graph
     */
    virtual void addEdge(int v, int w,int weight = 0) = 0;

    /*
     * Performs BFS on a given graph
     */
    virtual std::vector<int> BFS(int v,int to = 0) = 0;

    /*
     * Performs DFS on a given graph
     */
    virtual std::vector<int> DFS(int v) = 0;

    /*
     * Returns true if the graph is weighted
     */
    bool isWeighted();

    /*
     * Returns true if the graph is directed
     */
    bool isDirected();

    /*
     * Returns an int representing the number of nodes
     */
    int numOfNodes();

    /*
     * Print the graph
     */
    virtual void printGraph() = 0;

    /*
     * Activate printing during traversals and algorithms
     */
    void activatePrinting();

    /*
     * Deactivate printing during traversals and algorithms
     */
    void deactivatePrinting();

    /*
     * Returns true if printing functionality is activated
     */
    bool isPrintable();

    virtual std::vector<int> findConnectedComponents() = 0;

    virtual int returnCost(int v,int w) = 0;

    virtual ~Graph() = default;
};


#endif //GRAPH_GRAPH_H
