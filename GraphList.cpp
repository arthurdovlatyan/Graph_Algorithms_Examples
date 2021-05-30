//
// Created by arthurdovlat on 5/27/21.
//

#include "GraphList.h"

GraphList::GraphList(int numOfNodes) : Graph(numOfNodes) {
    adjList.reserve(numOfNodes);
    for (int i = 0; i < numOfNodes; ++i) {
        adjList.at(i).push_back(Nodes{i,0});
    }
}


GraphList::GraphList(GraphDirectnessType DirType, GraphWeightedType WeightType, int numOfNodes) : Graph(numOfNodes,DirType,WeightType) {
    adjList.reserve(numOfNodes);
    for (int i = 0; i < numOfNodes; ++i) {
        adjList.push_back(std::list<Nodes>());
    }
    for (int i = 0; i < numOfNodes; ++i) {
        adjList.at(i).push_back(Nodes{i,0});
    }
}


void GraphList::addEdge(int v, int w, int weight) {
    if (isDirected()) {
        if (isWeighted()) {
            adjList.at(v).push_back(Nodes{w,weight});
        } else {
            adjList.at(v).push_back(Nodes{w,weight});
        }
    } else {
        if (isWeighted()) {
            adjList.at(v).push_back(Nodes{w,weight});
            adjList.at(w).push_back(Nodes{v,weight});
        } else {
            adjList.at(v).push_back(Nodes{w,adjacent});
            adjList.at(w).push_back(Nodes{v,adjacent});
        }
    }
}

std::vector<int> GraphList::BFS(int v,int to) {
    std::vector<bool> visitedNodes(numOfNodes(), false);
    std::queue<int> queue;
    std::vector<int> path;
    visitedNodes.at(v) = true;
    queue.push(adjList.at(v).front().val);
    while (!queue.empty()) {
        auto i = queue.front();
        queue.pop();
        if (isPrintable()) {std::cout << i << " ";}
        std::list<Nodes> neighbours = adjList.at(i);
        for (auto a: neighbours) {
            if (a.val != 0 && (!visitedNodes.at(a.val))) {
                queue.push(a.val);
                if (to != -1)
                    path.push_back(a.val);
                visitedNodes.at(a.val) = true;
            }
        }
    }
    if (isPrintable()) { std::cout << std::endl;}
    return path;
}

void GraphList::DFSHelper(int v,std::vector<bool>& visitedNodes,std::vector<int>& path) {
    if (visitedNodes.at(v)) {
        return;
    }
    visitedNodes.at(v) = true;
    path.push_back(v);
    std::list<Nodes> neighbours = adjList.at(v);
    if (isPrintable()) {
        std::cout << v << " ";
    }

    for (auto a: neighbours) {
        if (!visitedNodes.at(a.val)) {
            if (isPrintable() && isWeighted()) {
                std::cout  << "-> "<< "cost (" << a.cost << ") ";
            }
            DFSHelper(a.val, visitedNodes,path);
        }
    }
}

std::vector<int> GraphList::DFS(int v) {
    if (isPrintable()) { std::cout << "DFS result: ";}
    std::vector<int> path;
    std::vector<bool> visitedNodes(numOfNodes() ,false);
    DFSHelper(v,visitedNodes,path);
    if (isPrintable()) { std::cout << std::endl; }
    return path;
}

GraphList::~GraphList() {

}

void GraphList::printGraph() {
    for (auto& a : adjList) {
        std::cout << a.front().val;
        auto it = a.begin();
        if (it->cost != 0) {
            std::cout <<  " -> " << it->val << " (cost " << it->cost << ") ";
        }
        it++;
        for (; it != a.end(); ++it) {
            std::cout <<  " -> " << it->val << " (cost " << it->cost << ") ";
        }
        std::cout << std::endl;
    }
}

int GraphList::returnCost(int v, int w) {
    if (!isWeighted()) {
        return -1;
    }
    auto it = std::find(adjList.at(v).begin(),adjList.at(v).end(),w);
    if (it != adjList.at(v).end()) {
        return it->cost;
    }
}

void GraphList::componentsHelper(int v,std::vector<bool>& visitedNodes,std::vector<int>& components,int count){
    if (v >= numOfNodes()) {
        return;
    }
    std::list<Nodes> neighbours = adjList.at(v);
    visitedNodes.at(v) = true;
    components.at(v) = count;
    for (auto& a: neighbours) {
        if (!visitedNodes.at(a.val)) {
            componentsHelper(a.val,visitedNodes,components,count);
        }
    }
}

std::vector<int> GraphList::findConnectedComponents() {
    std::vector<int> connectedComponents(numOfNodes(),0);
    int count = 0;
    std::vector<bool> vesitedNodes(numOfNodes(), false);
    for (int i = 0; i < adjList.size(); ++i) {
        if(!vesitedNodes.at(i)) {
            count++;
            componentsHelper(i,vesitedNodes,connectedComponents,count);
        }
    }
    return connectedComponents;
}

std::vector<int> GraphList::Dijkstra(int v,int end) {
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
        std::list<Nodes> neighbours = adjList.at(index);
        for (auto& x : neighbours) {
            int newDist = distance.at(index) + x.cost;
            if (newDist < distance.at(x.val)) {
                distance.at(x.val) = newDist;
                pq.push(std::make_pair(x.val, newDist));
            }
        }
    }
    return distance;
}

std::pair<int,std::vector<std::tuple<int,int,int>>> GraphList::Prim(int v) {
    auto i = std::pair<int,std::vector<std::tuple<int,int,int>>>();
    return i;
}




