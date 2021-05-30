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

std::vector<int> GraphMatrix::Dijkstra(int v,int end) {
    if (!isWeighted()) {
        throw std::runtime_error("Dijkstas algorithm requires the graph to be weighted");
    }
    std::vector<int> distance(numOfNodes(),std::numeric_limits<int>::max());
    std::vector<bool> visited(numOfNodes(), false);
    distance.at(v) = 0;
    auto cmp = [] (std::pair<int,int> a, std::pair<int,int> b) {return std::get<0>(a) < std::get<0>(b);};
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>, decltype(cmp)> pq;
    pq.push(std::make_pair(v,0));
    while (!pq.empty()) {
        int index = pq.top().first, minvalue = pq.top().second;
        pq.pop();
        visited.at(index) = true;
        for (int i = 0; i < numOfNodes(); ++i) {
            if (adjMatrix[index][i] != 0) {
                int newDist = distance.at(index) + adjMatrix[index][i];
                if (newDist < distance.at(i)) {
                    distance.at(i) = newDist;
                    pq.push(std::make_pair(i, newDist));
                }
            }
        }
    }
    return distance;
}

// TODO implement the Prims algoritm
std::pair<int,std::vector<std::tuple<int,int,int>>> GraphMatrix::Prim(int v) {
//    int n = numOfNodes();
//    auto cmp = [] (std::tuple<int,int,int> a, std::tuple<int,int,int> b) {return std::get<0>(a) < std::get<0>(b);};
//    std::priority_queue<std::tuple<int,int,int>,std::vector<std::tuple<int,int,int>>, decltype(cmp)> pq;
//    std::vector<bool> visited(numOfNodes(), false);
//    int m = n - 1;
//    int edgeCount = 0,mstCost = 0;
//    std::vector<std::tuple<int,int,int>> mstEdges(m);
//
//    visited.at(v) = true;
//
//    std::vector<int> edges = adjMatrix.at(v);
//    for (auto& edge: edges) {
//        if (!visited.at(edge)) {
//            pq.push(std::make_tuple(v,edge, returnCost(v,edge)));
//        }
//    }
//
//    while (!pq.empty() && edgeCount != m) {
//        auto edge = pq.top();
//        pq.pop();
//        if (visited.at(std::get<1>(edge))) {
//            continue;
//        }
//        mstEdges.at(edgeCount++) = edge;
//        mstCost += std::get<2>(edge);
//        std::vector<int> edges = adjMatrix.at(std::get<1>(edge));
//        for (auto& e: edges) {
//            if (!visited.at(e)) {
//                pq.push(std::make_tuple(std::get<1>(edge),e, returnCost(std::get<1>(edge),e)));
//            }
//        }
//
//    }
//    if (edgeCount != m) {
//        return std::make_pair(-1,std::vector<std::tuple<int,int,int>>());
//    }

//    return std::make_pair(mstCost,mstEdges);
}





