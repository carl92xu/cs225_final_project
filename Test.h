#pragma once
#include "Graph.h"
#include "parseGraph.h"
#include <iostream>
#include <unordered_set>
using namespace std;

class Test {
    public:
        void testParse(Graph g);
        void testBFSSmall();
        void testBFSLarge();
        void validateNodeNo(Graph g);
        void validateEdgeNo(Graph g);
        void validateNodeWithFile(Graph g);
        bool checkAiportExists(std::string abbr);
        void validateEdgeWithFile(Graph g);
        bool checkEdgeExists(std::string start, std::string end);
    private:
};