#include <iostream>
#include "Graph.hpp"
#include "GraphFileHandler.hpp"

void singleCoreEdf(Orca::Graph::Graph* graph) {

    // update deadlines

}

void printGraph(Orca::Graph::Graph* graph) {
    std::list<Orca::Graph::GraphNode*>* nodes = graph->getNodes();
    std::list<Orca::Graph::GraphNode*>::iterator i;

    std::cout << "NODES ========================================" << std::endl;
    Orca::Graph::GraphNodeData data;
    for (i = nodes->begin(); i != nodes->end(); i++) {
        data = *((*i)->getData());
        std::cout << data.id << "\t" << data.name << " "
            << "\t\t\t" << data.executionTime << std::endl;
    }

    std::list<Orca::Graph::GraphEdge*>* edges = graph->getEdges();
    std::list<Orca::Graph::GraphEdge*>::iterator j;

    std::cout << "EDGES ========================================" << std::endl;
    Orca::Graph::GraphEdgeData edata;
    for (j = edges->begin(); j != edges->end(); j++) {
        edata = *((*j)->getData());
        std::cout << (*j)->getFrom()->getData()->name
            << "\t" << (*j)->getTo()->getData()->name
            << edata.dataTransferTime << std::endl;
    }
}

int main(int argc, char** argv) {
    std::string filename = "examples-ogm/waters2019.otm";

    Orca::Graph::Graph* graph;
    graph = Orca::Graph::GraphFileHandler::parseFromFile(filename);

    if (graph == nullptr) {
        std::cout << "could not open file <" << filename << ">" << std::endl;
        return 1;
    }

    printGraph(graph);
    singleCoreEdf(graph);
}
