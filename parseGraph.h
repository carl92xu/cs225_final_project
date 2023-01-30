#pragma once
#include "Graph.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "parseGraph.h"


using namespace std;

class parseGraph {
    public:
        void parseCSV(Graph &g, std::ifstream &airport_ifs, std::ifstream &route_ifs);
    private:
        vector<string> delimit(string str_, string delimiter);
};