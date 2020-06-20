#include "graph.hpp"

int main(int argc, char* argv[])
{
    Output out;
    if(argc < 2)
        return out << "Invalid arguments.\n", 0;
    Graph graph;
    graph.read();
    out << "Strongly connected components (size: <nodes>):\n";
    clock_t t0 = clock();
    graph.find_scc(argv[1][0] - '0');
    clock_t t1 = clock();
    out << "\n";
    out << "\nNumber of nodes:      " << graph.node_count;
    out << "\nNumber of edges:      " << graph.edge_count;
    out << "\nNumber of SCCs:       " << graph.scc_count;
    out << "\nSize of largest SCC:  " << graph.largest_scc_size;
    out << "\nRunning time (input): " << int(1000 * t0 / CLOCKS_PER_SEC) << " ms";
    out << "\nRunning time (algo):  " << int(1000 * (t1 - t0) / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}
