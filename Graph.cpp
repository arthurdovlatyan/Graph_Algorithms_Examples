//
// Created by arthurdovlat on 5/27/21.
//

#include "Graph.h"

Graph::Graph() : mDirType(GraphDirectnessType::Undirected), mWeightType(GraphWeightedType::Unweighted) , MNodesNumber(0){}

Graph::Graph(int numOfNodes) : mDirType(GraphDirectnessType::Undirected), mWeightType(GraphWeightedType::Unweighted), MNodesNumber(numOfNodes) {}

Graph::Graph(int Nodes, GraphDirectnessType DirType, GraphWeightedType WeightType) : mDirType(DirType), mWeightType(WeightType), MNodesNumber(Nodes) {}

bool Graph::isWeighted() {
    return GraphWeightedType::Weighted == mWeightType;
}

bool Graph::isDirected() {
    return GraphDirectnessType::Directed == mDirType;
}

int Graph::numOfNodes() {
    return MNodesNumber;
}

void Graph::activatePrinting() {
    p = print::print;
}

void Graph::deactivatePrinting() {
    p = print::doNotPrint;
}

bool Graph::isPrintable() {
    return p == print::print;
}




