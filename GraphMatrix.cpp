//
// Created by arthurdovlat on 5/27/21.
//

#include "GraphMatrix.h"


GraphMatrix::GraphMatrix(int numOfNodes) : Graph(numOfNodes) {
    adjMatrix.reserve(numOfNodes);
    for (int i = 0; i < numOfNodes; ++i) {
        adjMatrix.push_back(std::vector<int>(numOfNodes));
        for(int j = 0; j < numOfNodes; ++j) {
            adjMatrix.at(i).at(j) = 0;
        }
    }
}

GraphMatrix::GraphMatrix(GraphDirectnessType DirType, GraphWeightedType WeightType, int numOfNodes) : Graph(numOfNodes,DirType,WeightType){
    adjMatrix.reserve(numOfNodes);
    for (int i = 0; i < numOfNodes; ++i) {
        adjMatrix.push_back(std::vector<int>(numOfNodes));
        for(int j = 0; j < numOfNodes; ++j) {
            adjMatrix.at(i).at(j) = 0;
        }
    }
}


void GraphMatrix::addEdge(int v, int w, int weight) {
    if (isDirected()) {
        if (isWeighted()) {
            adjMatrix.at(v).at(w) = weight;
        } else {
            adjMatrix.at(v).at(w) = adjacent;
        }
    } else {
        if (isWeighted()) {
            adjMatrix.at(v).at(w) = weight;
            adjMatrix.at(w).at(v) = weight;
        } else {
            adjMatrix.at(v).at(w) = adjacent;
            adjMatrix.at(w).at(v) = adjacent;
        }
    }
}
// TOD0 add ability to find the bath from to to v
std::vector<int> GraphMatrix::BFS(int v,int to) {
    std::vector<bool> visitedNodes(numOfNodes(), false);
    std::vector<int> path;
    std::queue<int> queue;
    queue.push(v);
    visitedNodes.at(v) = true;
    while (!queue.empty()) {
        int visited = queue.front();
        queue.pop();
        if (isPrintable()) { std::cout << visited << " ";}
        for (int i = 0; i < numOfNodes(); ++i) {
            if (adjMatrix[visited][i] != 0 && (!visitedNodes.at(i))) {
                queue.push(i);
                if (to != -1)
                    path.push_back(i);
                visitedNodes[i] = true;
            }
        }
    }
    if (isPrintable()) { std::cout << std::endl;}
    return path;
}

void GraphMatrix::DFSHelper(int v,std::vector<bool>& visitedNodes,std::vector<int>& path) {
    if (visitedNodes.at(v)) {
        return;
    }
    visitedNodes.at(v) = true;
    path.push_back(v);
    if (isPrintable()) {std::cout << v;}
    for (int i = 0; i < adjMatrix.at(v).size(); ++i) {
        if(adjMatrix[v][i] != 0 && !visitedNodes.at(i)) {
            if (isPrintable() && isWeighted()) { std::cout << " -> " << "cost (" << adjMatrix[v][i] << ") ";}
            DFSHelper(i,visitedNodes,path);
        }
    }
}

std::vector<int> GraphMatrix::DFS(int v) {
    if (isPrintable()) { std::cout << "DFS result: ";}
    std::vector<int> visitedPath;
    std::vector<bool> visitedNodes(numOfNodes() ,false);
    DFSHelper(v,visitedNodes,visitedPath);
    if (isPrintable()) { std::cout << std::endl; }
    return visitedPath;
}

GraphMatrix::~GraphMatrix() {
}

void GraphMatrix::printGraph() {
    std::cout << "    ";
    for (int i = 0; i < numOfNodes(); ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < numOfNodes(); ++i) {
        std::cout << i << "   ";
        for (int j = 0; j < numOfNodes(); ++j) {
            std::cout << adjMatrix.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

int GraphMatrix::returnCost(int v,int w) {
    if (!isWeighted()) {
        return -1;
    }
    return adjMatrix[v][w];
}

void GraphMatrix::componentsHelper(int v,std::vector<bool>& visitedNodes,std::vector<int>& components,int count) {
    if (v >= numOfNodes()) {
        return;
    }
    visitedNodes.at(v) = true;
    components.at(v) = count;
    for (int i = 0; i < numOfNodes();++i) {
        if (!visitedNodes.at(i) && adjMatrix[v][i] != 0) {
            componentsHelper(i,visitedNodes,components,count);
        }
    }
}

std::vector<int> GraphMatrix::findConnectedComponents() {
    std::vector<int> connectedComponents(numOfNodes(),0);
    int count = 0;
    std::vector<bool> vesitedNodes(numOfNodes(), false);
    for (int i = 0; i < adjMatrix.size(); ++i) {
        if(!vesitedNodes.at(i)) {
            count++;
            componentsHelper(i,vesitedNodes,connectedComponents,count);
        }
    }
    return connectedComponents;
}

