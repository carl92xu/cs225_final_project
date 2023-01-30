#include "Test.h"

/**
 * Validate whether the parsed graph has 7697 nodes (airports).
 * @param g The parsed graph
 */
void Test::validateNodeNo(Graph g){
    if(g.nodeNumber() != 7697){
        std::cout<<"test for number:" << g.nodeNumber()<<endl;
    }
    else{
        std::cout<<"The number of nodes (airports) is: " <<g.nodeNumber()<<", which is correct"<<endl;
    }
}

bool Test::checkAiportExists(std::string abbr){
    std::ifstream airport_ifs("./airports.dat");
    std::string line;
    for(unsigned int curLine = 0; getline(airport_ifs, line); curLine++) {
        if (line.find(abbr) != string::npos) {
            return true;
        }
    }
    return false;
}

void Test::validateNodeWithFile(Graph g){
    std::unordered_map<std::string, Graph::Node*> abbrMap = g.getAbbrMap();
    std::cout << "map size:" << abbrMap.size() << std::endl;
    bool wrong = false;
    for (const auto &myPair: abbrMap) {
        if (!checkAiportExists(myPair.first)) {
            std::cout << "cannot find: " << myPair.first << std::endl;
            wrong = true;
        }
    }
    if (wrong) {
        std::cout << "not all airports match with what inside source file" << std::endl;
    }
    else {
        std::cout << "all airports match with what inside source file" << std::endl;
    }
}

bool Test::checkEdgeExists(std::string start, std::string end){
    std::ifstream airport_ifs1("./route.dat");
    std::ifstream airport_ifs2("./route.dat");
    std::unordered_set<int> set1, set2;
    std::string line;
    for(unsigned int curLine = 0; getline(airport_ifs1, line); curLine++) {
        if (line.find(start) != string::npos) {
            set1.insert(curLine);
        }
    }
    for(unsigned int curLine = 0; getline(airport_ifs2, line); curLine++) {
        if (line.find(end) != string::npos) {
            set2.insert(curLine);
        }
    }
    //check whether two line idx equal
    for (int idx:set1) {
        if (!set2.count(idx)) {
            return false;
        }
    }
    return true;
}

void Test::validateEdgeWithFile(Graph g){
    std::vector<std::vector<Graph::Edge *>> edgeVec = g.getAdjList();
    bool wrong = false;
    for (size_t i = 0; i < edgeVec.size(); i++) {
        for (auto e:edgeVec[i]) {
            if (!checkEdgeExists(e->source->abbr, e->dest->abbr)) {
                wrong = true;
            }
        }
    }
    if (wrong) {
        std::cout << "not all edges match with what inside source file" << std::endl;
    }
    else {
        std::cout << "all edges match with what inside source file" << std::endl;
    }
}

/**
 * Validate whether the parsed graph has 67663 edges (distinct flight iternrary).
 * @param g The parsed graph
 */
void Test::validateEdgeNo(Graph g){
    if(g.edgeCount + g.delete_flights != 67663){
        cout<<g.edgeCount<<endl;
        cout<<"number of input flights is not correct"<<endl;
    }
    else{
        cout<<"Number of flights is: "<<g.edgeCount<<", which is correct"<<endl;
    }
}

/**
 * Validate whether the parsed graph's contains lat/lon data, airport abbreviation that adhere to format.
 * @param g The parsed graph
 */
void Test::testParse(Graph g) {
    for(auto &it:g.all_node){
        //check lat / lon 
        if((it->lat) < -90.0 || (it->lat) > 90.0){
            std::cout<< it->abbr<<endl;
            std::cout<<" The entered lat is out of range" << endl;
        }

        if((it->lon) < -180.0 || (it->lon) > 180.0){
            std::cout<< it->abbr<<endl;
            std::cout<<" The entered lon is out of range" << endl;
        }
        // check obtained abbr
        if((it->abbr.size()>4 || it->abbr.size()<3) ){
            if(it->abbr.size() != 0){
                std::cout << it->abbr << endl;
                //std::cout << it->name << endl;
                std::cout<<"The above abbr is not valid"<<endl; 
            }
                          
        } 

        for(size_t i = 0; i < it->abbr.size(); i++){
            if(!isupper(it->abbr[i]) && ! isdigit(it->abbr[i])){
                std::cout<< it->abbr<<endl;
                std::cout<<"The entered abbr is not valid"<<endl; 
            }
        }
        // //check name
        // for(int i =0;i < it->name.size();i++){
        //     if(!isalpha(it->name[i]) && it->name[i] != ' ' && it->name[i] != '/'&& it->name[i] != '\\'&& it->name[i] != '~'&& it->name[i] != '\''&& it->name[i] != '-'){
        //         std::cout<<it->name[i]<< std::endl;
        //         std::cout<< it->name<< std::endl;
        //         std::cout<<"The entered name is not valid"<< std::endl;
        //         break;
        //     }
        // } // suppose the condition is right. 
    }
}

void Test::testBFSSmall(){
    Graph g;
    parseGraph parser;

    std::string airportTest = "./airports_test_small.dat";
    std::string routesTest = "./routes_test_small.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.BFS("AER", "KZN");
    g.BFS("ASF", "KZN");
    g.BFS("ASF", "MRV");
}

void Test::testBFSLarge(){
    Graph g;
    parseGraph parser;

    std::string airportTest = "./airports_test_large.dat";
    std::string routesTest = "./routes_test_large.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.BFS("LAX", "BKK");
}
