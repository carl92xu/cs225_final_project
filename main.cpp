#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "Graph.h"
#include "vector"
#include "Test.h"
#include "parseGraph.h"

using namespace std;

int main() {
    Graph g;
    Test test;
    parseGraph parser;

    std::string airport = "./airports.dat";
    std::string routes = "./routes.dat";
    std::ifstream airport_ifs(airport);
    std::ifstream route_ifs(routes);

    // parse the graph
    parser.parseCSV(g, airport_ifs, route_ifs); 
    // test the parsed graph
    test.testParse(g);
    test.validateNodeNo(g);
    test.validateEdgeNo(g);
    //test.validateNodeWithFile(g);
    //test.validateEdgeWithFile(g);
    // test running BFS
    test.testBFSSmall();
    test.testBFSLarge();
}