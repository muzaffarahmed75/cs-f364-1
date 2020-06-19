#include <vector>
#include <stack>
#include <unordered_map>
#include <numeric>
#include <random>
#include <chrono>
#include "io.hpp"

/**
 * Implements two algorithms to find the strongly-connected components in a directed graph.
 * scc_dfs() implements the DFS (Kosaraju's) algorithm, while dcsc() implements a
 * divide-and-conquer algorithm.
 */
class Graph
{
    int n;  ///< Number of nodes in the graph.
    std::vector<std::vector<int>> adj;  ///< Adjacency list representing the graph.
    std::vector<std::vector<int>> rev;  ///< Transpose of #adj.
    std::unordered_map<std::string, int> compress;  ///< Coordinate compression map.
    std::vector<std::string> decompress;    ///< Coordinate decompression, inverse of #compress.
    std::mt19937 rng;   ///< Random number generator (Mersenne Twister 19937) engine instance.

    void scc_dfs_util_dfs1(int, std::vector<bool>&, std::stack<int>&);
    void scc_dfs_util_dfs2(int, std::vector<bool>&, std::vector<int>&);
    void scc_dfs();
    void dcsc(std::vector<int>&);
    void dcsc_util_dfs(std::vector<std::vector<int>>&, int, std::vector<bool>&);

public:
    int scc_count;  ///< Count of SCCs found.
    int largest_scc_size;   ///< Size of the largest SCC found.
    int node_count; ///< Number of nodes, same as #n except access.
    int edge_count; ///< Number of edges in the input graph (including repetitions).

    Graph();
    void read();
    void find_scc(int);
};
