#include "Graph.h"

Graph::Graph() {
    edges = {};
    wasVisited = {};
    postOrder = {};
    SCClist={};
}

void Graph::BuildGraph(std::vector<Rule *> rules) {
    std::map<int, std::string> ruleToNum;
    // Convert the predicate names to rule numbers
    for (int i = 0; i < (signed)rules.size(); i++) {
        //ruleToNum.insert(std::pair<int, std::string>(i, rules.at(i)->GetHeadPredicate()->GetId()));
        ruleToNum.insert({i, rules.at(i)->GetHeadPredicate()->GetId()});
    }

    // Create the adjacency list
    for (int i = 0; i < (signed)rules.size(); i++) {
        std::set<int> dependOnRule = {};
        // Create the set of rules it depends on
        for (unsigned int j = 0; j < rules.at(i)->GetBodyPredicatesSize(); j++) {
            for (auto it = ruleToNum.begin(); it != ruleToNum.end(); ++it)
                if (it->second == rules.at(i)->GetBodyPredicateAtIndex(j)->GetId()) {
                    dependOnRule.insert(it->first);
                }
        }
        edges.insert({i, dependOnRule});
    }

    // Print out the graph
    std::cout << "Dependency graph" << std::endl;
    for (std::map<int, std::set<int>>::iterator it = edges.begin(); it != edges.end(); it++) {
        std::cout << "R" << std::to_string(it->first) << ":";
        /*for(auto x : it->second) {
            std::cout << "R" << x << ",";
        }*/
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            std::cout << "R" << *it2;
            if (it2 != std::prev(it->second.end(), 1)) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }

}

// Takes the forward dependency graph and reverses it
void Graph::BuildReverseGraph() {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            reverseEdges[*it2].insert(it->first);
        }
    }

    // Print out the graph
    /*for (std::map<int, std::set<int>>::iterator it = reverseEdges.begin(); it != reverseEdges.end(); it++) {
        std::cout << "R" << std::to_string(it->first) << ":";
        for(auto x : it->second) {
            std::cout << "R" << x << ",";
        }
        std::cout << std::endl;
    }*/
}

void Graph::DFSforForwardTree(int vertex, std::vector<int> &tree) {
    wasVisited[vertex] = true;
    for (auto it = edges[vertex].begin(); it!= edges[vertex].end(); it++) {
        if (wasVisited[*it] != true) {
            DFSforForwardTree(*it, tree);
        }
    }
    tree.push_back(vertex);
}

void Graph::DFSforPostOrder(int vertex) {
    wasVisited[vertex] = true;
    for (auto it = reverseEdges[vertex].begin(); it!= reverseEdges[vertex].end(); it++) {
        if (wasVisited[*it] != true) {
            DFSforPostOrder(*it);
        }
    }
    postOrder.push_back(vertex);
}

void Graph::ResetWasVisitedFlag() {
    for (unsigned int i = 0; i < edges.size(); i++) {
        wasVisited[i] = false;
    }
}

std::vector<int> Graph::DFScreateTree(int vertex, std::vector<int> DFStree) {
    wasVisited[vertex] = true;
    for (auto it = edges[vertex].begin(); it != edges[vertex].end(); it++) {
        if (wasVisited[*it] != true) {
            DFScreateTree(*it, DFStree);
        }
    }
    DFStree.push_back(vertex);

    return DFStree;

}

void Graph::DFSforestForPostOrder() {
    for (unsigned int i = 0; i < reverseEdges.size(); i++) {
        if (wasVisited[i] == false) {
            DFSforPostOrder(i);
        }
    }
    for (unsigned int i = 0; i < edges.size(); i++) {
        if (wasVisited[i] == false) {
            DFSforPostOrder(i);
        }
    }
}

void Graph::DFSforestForSCCs(){
    ResetWasVisitedFlag();
    for (int i = (signed)postOrder.size() - 1; i >= 0; i--) {
         if (wasVisited[postOrder.at(i)] == false) {
            std::vector<int> tree = {};
            DFSforForwardTree(postOrder.at(i), tree);
            std::sort(tree.begin(), tree.end());
            SCClist.push_back(tree);
        }
    }

}

std::vector<std::vector<int>> Graph::FindSCCs(std::vector<Rule *> rules) {
    BuildGraph(rules);
    BuildReverseGraph();
    //dependencyGraph.DFSforPostOrder(0);
    DFSforestForPostOrder();
    DFSforestForSCCs();
    //dependencyGraph.PrintPostOrder();
    // Temporary to print the SCCS
    /*for (unsigned int i = 0; i < SCClist.size(); i++) {
        std::cout << "Component " << i << ": ";
        for (unsigned j = 0; j < SCClist.at(i).size(); j++) {
            std::cout << SCClist.at(i).at(j) << ", ";
        }
        std::cout << std::endl;
    }*/

    return SCClist;
}

std::string Graph::PrintSCCAtIndex(int index) {
    std::string retString = "";
    for (unsigned int i = 0; i < SCClist.at(index).size(); i++) {
        retString.append("R" + std::to_string(SCClist.at(index).at(i)));
        if (i < SCClist.at(index).size()-1) {
            retString.append(",");
        }
    }
    return retString;
}

bool Graph::SelfDependent(int key) {
    for (auto it = edges[key].begin(); it != edges[key].end(); it++) {
        if (*it == key) {
            return true;
        }
    }
    return false;
}


void Graph::PrintPostOrder() {
    std::cout << "Post order: ";
    for (unsigned int i = 0; i < postOrder.size(); i++) {
        std::cout << std::to_string(postOrder.at(i)) << " ";
    }
    std::cout << std::endl;
}