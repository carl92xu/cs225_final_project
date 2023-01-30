#define _USE_MATH_DEFINES

#include <cmath>
#include "Graph.h"
#define Earth_radius 6371e3

using std::priority_queue;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::string;

Graph::Graph() {
    adjSize = 0;
    edgeCount = 0;
    delete_flights = 0;
};

Graph::~Graph() {

};

void Graph::addNode(Node* n) {
    n->modifyIndex(adjSize);   // update node n's vector 
    std::vector<Edge *> tmp;
    adjList.push_back(tmp); // update our adjList
    idNodeMap[adjSize] = n;   // update HashMap  
    abbrNodeMap[n->abbr] = n; // update HashMap 
    adjSize += 1;              // increment # of nodes
    all_node.push_back(n);
}

void Graph::addEdge(Edge* e) {
    adjList[e->source->vecIndex].push_back(e);
    edgeCount ++; //add for testcase; 
}

int Graph::nodeNumber() {
    return adjList.size();
}
// void Graph::addEdge(Edge* e) {

// }
std::unordered_map<std::string, Graph::Node*> Graph::getAbbrMap() {
    return abbrNodeMap;
}

Graph::Node* Graph::abbr_to_Node(std::string abbr){
    try {
        return abbrNodeMap.at(abbr);
    } catch (std::out_of_range& e){
        std::cerr << e.what() << std::endl;
        std::cout << "abbr: " << abbr << std::endl;
    }
}

Graph::Node* Graph::id_to_Node(int id) {
    return idNodeMap.at(id);
}

void Graph::printMap(){
    for (auto it = abbrNodeMap.cbegin(); it != abbrNodeMap.cend(); ++it) {
        if ((*it).first == "AER") {
            std::cout << "count: " << abbrNodeMap.count("AER") << std::endl;
        std::cout << "abbr: " << (*it).first << std::endl;
        }
    }
}
bool Graph::exists(std::string abbr) {
    if (abbrNodeMap.count(abbr)) {
        //std::cout << abbr << " exists" << std::endl;
        return true;
    }
    return false;
}
//double check the correctness
//formula from https://www.movable-type.co.uk/scripts/latlong.html
double Graph::computeDist(Node* src, Node* dest){
    double latSrc = (src->lat)/180.0; //src lat in radian
    double latDest = (dest->lat)/180.0; //dest lat in radian
    double lat_diff = (latDest-latSrc) * M_PI/180.0; //latitude difference
    double lon_diff = ((dest->lon) - (src->lon)) * M_PI / 180.0; //longitude difference
    double a = sin(lat_diff/2.0)*sin(lat_diff/2.0) + cos(latSrc)*cos(latDest) + sin(lon_diff/2.0)*sin(lon_diff/2.0); 
    double c = 2.0 * atan2(sqrt(a),sqrt(1.0-a));
    double final_distance = Earth_radius * c;
    return final_distance;
}
std::vector<std::vector<Graph::Edge *>> Graph::getAdjList() {
    return adjList;
}

void Graph::BFS(std::string src, std::string dest) {
    std::cout << "printing BFS traversal" << std::endl;
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> predecessor;
    q.push(src);
    visited.insert(src);
    while (!q.empty()) {
        std::string cur = q.front();  // pop the current Abbr from queue
        //std::cout << "node: " << cur << std::endl;
        q.pop();
        if (cur == dest) {
            break;
        }
        Node * curAbbr = abbr_to_Node(cur);
        //std::cout << "idx: " << curAbbr->vecIndex << " abbr: " << curAbbr->abbr << std::endl;
        for (Edge* e: adjList[curAbbr->vecIndex]) {
            if (visited.count(e->dest->abbr) == 0) { // not visited
                visited.insert(e->dest->abbr);
                q.push(e->dest->abbr);
                
                predecessor[e->dest->abbr] = curAbbr->abbr;
                //std::cout << "dest: " << e->dest->abbr << " cur: " << curAbbr->abbr << std::endl;
            }
        }
    }
    std::vector<std::string> res;
    std::string cur = dest;
    res.push_back(cur);
    // cur = predecessor[cur];
    while (predecessor.count(cur)) {
        //std::cout << "cur is: " << cur << std::endl;
        cur = predecessor[cur];
        res.push_back(cur);
    }
    std::reverse(res.begin(), res.end());
    for (std::string s:res) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}
void Graph::increment_delete_flights(){
    delete_flights ++;
}




//make sure the string are the abbreviation
void Graph::AStar(std::string start, std::string dest){
    std::cout << "START ASTAR SHORTEST PATH SEARCH" << std::endl;


    //the starting Node
    Node* begin = abbr_to_Node(start);
    //the ending point
    Node* end = abbr_to_Node(dest);
    
    cout << "Start: " << begin->abbr << "\nDestination: " << end->abbr <<endl;
    //set the gscore to be 0 and fsore to be the distance
    begin->gscore = 0.0;
    begin->fscore = computeDist(begin, end);

    //initialized the priority queue with custom comparator 
    priority_queue<Node*, vector<Node*>, Comparator> pq;
    
    unordered_map<Node*, bool> visited; //close list

    pq.push(abbr_to_Node(start));
    
    //if we reach the destination
    bool reach = false;
    //keep looping until pq is empty
    while(!pq.empty()){
        Node * current = pq.top();
        pq.pop();
        
        //reach the destination
        if(current == end){
            reach = true;
            break;
        }
        
        visited.insert({current, true});
        
        //getting the adjacent edge list for the current node
        //to obtain all the neighbor nodes
        int index = current->vecIndex;
        for(Edge* edge: adjList[index]){
            
            //你java 上写的好像只有 g score 没有 f score
            if(visited.find(edge->dest) == visited.end()){
                //adjacent node fscore = gscore + distance between neighor to destination
                (edge->dest)->fscore = (current->gscore) + computeDist((edge->dest), end);
                //Compute g score, g score of neighbor = g score of current node + distance between neighbor and current node
                double distToDest = current->gscore + computeDist(current,(edge->dest));
                if(distToDest < (edge->dest)->gscore){
                    (edge->dest)->fscore = distToDest; 
                    pq.push((edge->dest));
                    (edge->dest)->prev= current;
                }
            }
        }

    }
    
    if(!reach){
        cout << "Path does not exist!" << endl;
        return;
    }
    
    vector<string> path;
    while(end!=nullptr){
        path.push_back(end->abbr);
        end = end -> prev;
    }
    while(!path.empty()){
        cout << " ----> " << path.back();
        path.pop_back();
    }
    cout << endl;
}