//
// Created by arthurdovlat on 5/27/21.
//

#ifndef GRAPH_GRAPHEXAMPLES_H
#define GRAPH_GRAPHEXAMPLES_H

#include "Graph.h"
#include "GraphMatrix.h"
#include "GraphList.h"
#include <memory>

class GraphExamples {
private:
    std::unique_ptr<Graph> mGraph;
    int number_of_examples = 3;
public:
    GraphExamples() = default;

    void previewPreDefinedGraphs() {
        std::cout << "Example number 1." << std::endl;
        std::cout << "Graph list Undirected weighted graph with 9 nodes." << std::endl;
        std::cout << " \n"
                     "               (2)        (7)\n"
                     "            1--------2 --------3 _\n"
                     "        (4)-         | |       |   - _  (9)\n"
                     "       -          (2)|   |     |        _\n"
                     "     0               8    |    | (14)     4\n"
                     "       -      (7) -  | (6) |   |      ---\n"
                     "       (8)-    --    |       | |   -  (10)\n"
                     "           7--------6 ---------5 -\n"
                     "              (1)         (2)                  " << std::endl;
        std::cout << "Example number 2." <<std::endl;
        std::cout << "Graph Matrix Undirected weighted graph with 9 nodes." << std::endl;
        std::cout << " \n"
                     "               (2)        (7)\n"
                     "            1--------2 --------3 _\n"
                     "        (4)-         | |       |   - _  (9)\n"
                     "       -          (2)|   |     |        _\n"
                     "     0               8    |    | (14)     4\n"
                     "       -      (7) -  | (6) |   |      ---\n"
                     "       (8)-    --    |       | |   -  (10)\n"
                     "           7--------6 ---------5 -\n"
                     "              (1)         (2)                  " << std::endl;
        std::cout << "Example number 3." <<std::endl;
        std::cout << "Graph List Undirected Unweighted graph with 6 nodes." << std::endl;
        std::cout << " \n"
                     "                     \n"
                     "            1            3\n"
                     "          - |            | - \n"
                     "       -    |            |   -\n"
                     "     0 -----2            4 ---- 5\n"
                     "        " << std::endl;
    }

    void loadPredefinedGraphs() {
        std::cout << "Choose a number corresponding to the example number of the graphs(choose number less than 0 to exit)." << std::endl;
        int n;
        previewPreDefinedGraphs();
        std::cin >> n;
        if (n < 0 || n > number_of_examples) {
            return;
        }
        std::cout << "You choose #" << n << std::endl;
        if (n == 1) {
            mGraph = std::make_unique<GraphList>(GraphDirectnessType::Undirected,GraphWeightedType::Weighted,9);
            mGraph->addEdge(0,1,4);
            mGraph->addEdge(0,7,8);
            mGraph->addEdge(1,2,8);
            mGraph->addEdge(1,7,11);
            mGraph->addEdge(7,8,7);
            mGraph->addEdge(7,6,1);
            mGraph->addEdge(2,8,2);
            mGraph->addEdge(2,3,7);
            mGraph->addEdge(2,5,4);
            mGraph->addEdge(6,8,6);
            mGraph->addEdge(6,5,2);
            mGraph->addEdge(3,4,9);
            mGraph->addEdge(3,5,14);
            mGraph->addEdge(5,4,10);
            mGraph->printGraph();
        } else if (n == 2) {
            mGraph = std::make_unique<GraphMatrix>(GraphDirectnessType::Undirected,GraphWeightedType::Weighted,9);
            mGraph->addEdge(0,1,4);
            mGraph->addEdge(0,7,8);
            mGraph->addEdge(1,2,8);
            mGraph->addEdge(1,7,11);
            mGraph->addEdge(7,8,7);
            mGraph->addEdge(7,6,1);
            mGraph->addEdge(2,8,2);
            mGraph->addEdge(2,3,7);
            mGraph->addEdge(2,5,4);
            mGraph->addEdge(6,8,6);
            mGraph->addEdge(6,5,2);
            mGraph->addEdge(3,4,9);
            mGraph->addEdge(3,5,14);
            mGraph->addEdge(5,4,10);
            mGraph->printGraph();
        } else if (n == 3) {
            mGraph = std::make_unique<GraphList>(GraphDirectnessType::Undirected,GraphWeightedType::Unweighted,6);
            mGraph->addEdge(0,1);
            mGraph->addEdge(1,2);
            mGraph->addEdge(0,2);
            mGraph->addEdge(3,4);
            mGraph->addEdge(3,5);
            mGraph->addEdge(4,5);
            mGraph->printGraph();
        }
        perform_Action();
        mGraph.release();
    }

    void resetGraph() {
        mGraph.release();
    }

    void createGraph() {
        int NumOfNodes;
        GraphDirectnessType directness;
        char ch;
        char repr;
        GraphWeightedType weightedness;
        std::cout << "Do you want underlying representation to be a LL(y/n):";
        std::cin >>repr;
        std::cout << "How many nodes your graph will have: ";
        std::cin >> NumOfNodes;
        std::cout << "Do you want your graph to be directed(y/n): ";
        std::cin >> ch;
        directness = ((ch == 'y') ? GraphDirectnessType::Directed : GraphDirectnessType::Undirected);
        std::cout << "Will the graph be waited: ";
        std::cin >> ch;
        weightedness = ((ch == 'y') ? GraphWeightedType::Weighted : GraphWeightedType::Unweighted);
        int maxNumber_Of_edges = directness==GraphDirectnessType::Directed ?  (NumOfNodes * (NumOfNodes-1)) : (NumOfNodes* (NumOfNodes-1)/2);
        if (repr == 'y') {
            mGraph = std::make_unique<GraphList>(directness,weightedness,NumOfNodes);
        } else {
            mGraph = std::make_unique<GraphMatrix>(directness,weightedness,NumOfNodes);
        }
        std::cout << "Enter the edges in the way of start end weight(if you want to stop enter -1)";
        for (int i = 0; i < maxNumber_Of_edges; ++i) {
            int start = 0,end = 0,cost = 0;
            std::cin >> start;
            std::cin >> end;
            std::cin >> cost;
            if (start == -1 || end == -1) {
                break;
            }
            mGraph->addEdge(start,end,cost);
        }
        std::cout << std::endl;
    }

    void printGraph() {
        if (mGraph == nullptr) {
            std::cout << "Graph is empty either choose it or create one." << std::endl;
            return;
        }
        mGraph->printGraph();
        return;
    }

    void perform_Action() {
        if (mGraph == nullptr) {
            std::cout << "First create a graph or load a predefined one." << std::endl;
            return;
        }
        int n;
        std::cout << "To perform a DFS choose 1." << std::endl;
        std::cout << "To perform a BFS choose 2." << std::endl;
        std::cout << "To perform a connected component search choose 3." << std::endl;
        std::cout << "To perform a Lazy Dijkstas algorithm choose 4." << std::endl;
//        std::cout << "To perform a Lazy Prims algorithm choose 5." << std::endl;
        std::cout << "To exit choose -1." << std::endl;
        while (true) {
            std::cout << "Enter number: ";
            std::cin >> n;
            if(n == -1) {
                return;
            } else if (n == 1) {
                int i;
                char ch;
                std::cout << "Do you want to unable printing(y/n): ";
                std::cin >> ch;
                if (ch == 'y') {
                    mGraph->activatePrinting();
                }
                std::cout << "From which node to start: ";
                std::cin >> i;
                if (i >= 0 && i < mGraph->numOfNodes()) {
                    std::vector<int> a = mGraph->DFS(i);
                } else {
                    std::cout << "Choose number corresponding to the number of nodes." << std::endl;
                    continue;
                }
            }
            else if (n == 2) {
                int j;
                char c;
                std::cout << "Do you want to unable printing(y/n): ";
                std::cin >> c;
                if (c == 'y') {
                    mGraph->activatePrinting();
                }
                std::cout << "From which node to start: ";
                std::cin >> j;
                if (j >= 0 && j < mGraph->numOfNodes()) {
                    std::vector<int> a = mGraph->BFS(j);
                } else {
                    std::cout << "Choose number corresponding to the number of nodes." << std::endl;
                    continue;
                }
            } else if (n == 3) {
                std::vector<int> g = mGraph->findConnectedComponents();
                int max = *std::max_element(g.begin(), g.end());
                for (int j = 1; j <= max; ++j) {
                    std::cout << "Group " << j << ": ";
                    for (int k = 0; k < g.size(); ++k) {
                        if (g.at(k) == j) {
                            std::cout << k << " ";
                        }
                    }
                    std::cout << std::endl;
                }
            } else if (n == 4) {
                int a;
                int b;
                std::cout << "From which node to start: ";
                std::cin >> a;
                std::cout << "Do you want to specify an end node: (-1 if no else number of node): ";
                std::cin >> b;
                if (a >= 0 && a < mGraph->numOfNodes()) {
                    if (b > -1 && b < mGraph->numOfNodes()) {
                        std::vector<int> d = mGraph->Dijkstra(a, b);
                        for (int i = 0; i < mGraph->numOfNodes(); ++i) {
                            std::cout << i << " ";
                        }
                        std::cout << std::endl;
                        for (int i = 0; i < d.size(); ++i) {
                            std::cout << d.at(i) << " ";
                        }
                        std::cout << std::endl;
                    } else {
                        std::vector<int> d = mGraph->Dijkstra(a);
                        for (int i = 0; i < mGraph->numOfNodes(); ++i) {
                            std::cout << i << " ";
                        }
                        std::cout << std::endl;
                        for (int i = 0; i < d.size(); ++i) {
                            std::cout << d.at(i) << " ";
                        }
                        std::cout << std::endl;
                    }
                } else {
                    std::cout << "Choose number corresponding to the number of nodes." << std::endl;
                    continue;
                }
//            } else if (n == 5) {
//                int a;
//                std::cout << "From which node to start: ";
//                std::cin >> a;
//                if (a >= 0 && a < mGraph->numOfNodes()) {
//                    auto d = mGraph->Prim(a);
//                    if (d.first == -1) {
//                        std::cout << "No prims minimum spanning tree is possible.";
//                    } else {
//                        std::cout <<"Cost: " <<d.first << std::endl;
//                        for (int i = 0; i < d.second.size(); ++i) {
//                            std::cout << get<0>(d.second.at(i)) << " " << get<1>(d.second.at(i))<< " " << get<2>(d.second.at(i)) << std::endl;
//                        }
//                    }
//                } else {
//                    std::cout << "Choose number corresponding to the number of nodes." << std::endl;
//                    continue;
//                }
//            }
        }
    }
};

#endif //GRAPH_GRAPHEXAMPLES_H
