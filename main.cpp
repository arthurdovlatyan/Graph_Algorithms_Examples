#include <iostream>
#include "Graph.h"
#include "GraphList.h"
#include "GraphMatrix.h"
#include "GraphExamples.h"

void runner() {
    GraphExamples g;
    while (true) {
        std::cout << "Option 1 load a predefined graph."<< std::endl;
        std::cout << "Option 2 Create your own." << std::endl;
        std::cout << "Option 3 Clear graph." << std::endl;
        std::cout << "Option -1 exit." << std::endl;
        int n;
        std::cin >> n;
        if (n == -1) {
            return;
        } else if (n == 1){
            g.loadPredefinedGraphs();
        } else if (n == 2) {
            g.createGraph();
        } else if (n == 3) {
            g.resetGraph();
        }
    }

}

int main() {
    runner();
}
