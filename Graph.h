#pragma once
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <limits>

class Graph {
    public:
        struct Node {
            int vecIndex;
            Node* prev;
            double lat;
            double lon;
            double fscore;
            double gscore;
            double hscore;
            std::string name; // airport fullname
            std::string abbr; // airport abbreviation
            Node() {}
            Node(int vecIndex, double lat, double lon, std::string name, std::string abbr) 
                : vecIndex(vecIndex), lat(lat), lon(lon), name(name), abbr(abbr) 
            {
                // not init vecIndex
            }
            void modifyIndex(int newIndex) {
                this->vecIndex = newIndex;
            }
        };

        struct Edge {
            Node *source;
            Node *dest;

            Edge() {}
            Edge(Node* n1, Node* n2) 
                : source(n1), dest(n2)
            {
            }
        };

    public:
        Graph();
        ~Graph();
        std::vector<Node*> all_node;  
        std::unordered_map<std::string, Graph::Node*> getAbbrMap();
        std::vector<std::vector<Graph::Edge *>> getAdjList();
        void addNode(Node* n);
        void addEdge(Edge* e);
        int nodeNumber();
        double computeDist(Node* src, Node* dest);
        Node* abbr_to_Node(std::string abbr);
        Node* id_to_Node(int id);
        bool exists(std::string abbr);
        void printMap();
        void BFS(std::string src, std::string dest);
<<<<<<< HEAD
 
=======
        int edgeCount ; // add for testcase. 
        int delete_flights; // add for testcase.
        void increment_delete_flights(); //add for testcase


        //AStar Search priority queue comparator
        typedef struct Compare{
            bool operator()(const Node*node1, const Node*node2){
                return node1->fscore < node2->fscore;
            }
        }Comparator;
        
        //this is the A start search algo
        void AStar(std::string start, std::string dest);


>>>>>>> de333d76abbf14af533fd3b3a8ce1d672e27e64d
    private:
        int adjSize;
        std::unordered_map<int, Node*> idNodeMap; // HM that converts id to node ptr
        std::unordered_map<std::string, Node*> abbrNodeMap; // HM that converts id to node ptr
        std::vector<std::vector<Edge *>> adjList;  // [ORD:[e1:[ EWR], e2: [HKG], e3[JFK]     
};