#ifndef PROJECT1_STARTER_CODE_GRAPH_H
#define PROJECT1_STARTER_CODE_GRAPH_H

#include <map>
#include <set>
#include <vector>
#include <string>
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"

class Graph {
private:
    std::map<int, std::set<int>> edges;
    std::map<int, std::set<int>> reverseEdges;
    std::map<int, bool> wasVisited;
    std::vector<int> postOrder;
    std::vector<std::vector<int>> SCClist;

    void DFSforPostOrder(int vertex);
    void DFSforForwardTree(int vertex, std::vector<int> &tree);
    void ResetWasVisitedFlag();

public:
    Graph();
    void BuildGraph(std::vector<Rule*> rules);
    void BuildReverseGraph();
    void DFSforestForPostOrder();
    std::vector<int> DFScreateTree(int vertex, std::vector<int> DFStree);
    void PrintPostOrder();
    std::vector<std::vector<int>> FindSCCs(std::vector<Rule*> rules);
    void DFSforestForSCCs();
    std::string PrintSCCAtIndex(int index);
    bool SelfDependent(int key);

};

#endif //PROJECT1_STARTER_CODE_GRAPH_H
