#pragma once

#include <iostream>
#include <string>
// #include <algorithm>
// #include <unordered_map>
// #include <vector>
// #include <queue>

#include "../Graph.h"

using namespace std;

// this is a helper function to find the shortest distance between two airports
// the ultimal goal is to find the shortest path between every pair of airports
// RETURN the sequence of airport names of the shortest path
string floydwarshall(Graph graph, string src, string dest);