//
// Created by arthurdovlat on 5/27/21.
//

#ifndef GRAPH_UTILITY_H
#define GRAPH_UTILITY_H

// A graph can either be directed or undirected
enum class GraphDirectnessType {
    Directed,
    Undirected
};


// A graph can either be weighted or unweighted
enum class GraphWeightedType {
    Weighted,
    Unweighted
};


// Enum indicating printing during traversals
enum class print {
    print,
    doNotPrint
};
#endif //GRAPH_UTILITY_H
