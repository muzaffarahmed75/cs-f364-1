#include "graph.hpp"

/**
 * Constructor. Initializes #scc_count and #largest_scc_size to appropriate values.
 * Seeds #rng with the current time.
 */ 
Graph::Graph()
{
    scc_count = 0;
    largest_scc_size = 1;
    rng.seed((int)std::chrono::steady_clock::now().time_since_epoch().count());
}

/**
 * A utility DFS function for use in scc_dfs().
 * @param[in] u Current vertex.
 * @param[in] vis Vector of boolean values with visited nodes set as true.
 * @param[out] st Stack of nodes visited so far, topmost in the stack being
 * the first to be found in the DFS.
 */
void Graph::scc_dfs_util_dfs1(int u, std::vector<bool>& vis, std::stack<int>& st)
{
    vis.at(u) = true;
    for(int v : adj.at(u))
        if(not vis.at(v))
            scc_dfs_util_dfs1(v, vis, st);
    st.push(u);
}

/**
 * Another utility DFS function for use in scc_dfs().
 * @param[in] u Current vertex.
 * @param[in,out] vis Vector of boolean values with visited nodes set as true.
 * @param[out] scc Current Strongly Connected Component.
 */
void Graph::scc_dfs_util_dfs2(int u, std::vector<bool>& vis, std::vector<int>& scc)
{
    if(vis.at(u))
        return;
    vis.at(u) = true;
    scc.push_back(u);
    for(int v : rev.at(u))
        if(not vis.at(v))
            scc_dfs_util_dfs2(v, vis, scc);
}

/**
 * Finds and prints all the SCCs in the graph represented by #adj. Uses DFS
 * (Kosaraju's algorithm) to find the SCCs.
 */
void Graph::scc_dfs()
{
    Output out;
    std::vector<bool> vis(n, false);
    std::stack<int> st;
    for(int u = 0; u < n; ++u)
        if(not vis[u])
            scc_dfs_util_dfs1(u, vis, st);
    std::fill(vis.begin(), vis.end(), false);
    while(st.size())
    {
        int u = st.top();
        st.pop();
        scc_count += not(vis[u]);
        std::vector<int> scc;
        scc_dfs_util_dfs2(u, vis, scc);
        if(scc.size())
        {
            out << int(scc.size()) << ": ";
            for(int it : scc)
                out << decompress.at(it) << ' ';
            out << '\n';
            if(scc.size() > largest_scc_size)
                largest_scc_size = scc.size();
        }
    }
}

/**
 * A utility DFS function for use in dcsc().
 * @param[in] g Adjacency representation of the current subgraph.
 * @param[in] u Current vertex.
 * @param[in,out] vis Vector of boolean values with visited nodes set as true.
 */
void Graph::dcsc_util_dfs(std::vector<std::vector<int>>& g, int u, std::vector<bool>& vis)
{
    vis.at(u) = true;
    for(int v : g.at(u))
        if(not vis.at(v))
            dcsc_util_dfs(g, v, vis);
}

/**
 * Finds and prints all the SCCs in the graph represented by #adj. Uses the DCSC
 * (Divide and Conquer Strongly-connected Components) algorithm to find SCCs.
 * @param[in] vers Nodes of the current subgraph.
 */
void Graph::dcsc(std::vector<int>& vers)
{
    Output out;
    if(vers.empty())
        return;
    bool has_edges = false;
    for(int v : vers)
        if(not adj.at(v).empty())
            has_edges = true;
    if(not has_edges)
    {
        for(int ver : vers)
            out << "1: " << decompress.at(ver) << '\n';
        scc_count += int(vers.size());
        return;
    }
    std::uniform_int_distribution<int> dist(1, (int)vers.size());
    int random_vertex = vers.at(dist(rng) - 1);
    std::vector<int> desc, pred, scc, rem;
    std::vector<bool> visd(n, true), visp(n, true);
    for(int ver : vers)
        visd.at(ver) = visp.at(ver) = false;
    dcsc_util_dfs(adj, random_vertex, visd);
    dcsc_util_dfs(rev, random_vertex, visp);
    for(int ver : vers)
    {
        if(visd.at(ver) and visp.at(ver))
            scc.push_back(ver);
        else if(visd.at(ver))
            desc.push_back(ver);
        else if(visp.at(ver))
            pred.push_back(ver);
        else
            rem.push_back(ver);
    }
    if(scc.size())
    {
        out << int(scc.size()) << ": ";
        ++scc_count;
        for(int it : scc)
            out << decompress.at(it) << ' ';
        out << '\n';
        if(scc.size() > largest_scc_size)
            largest_scc_size = scc.size();
    }
    dcsc(desc);
    dcsc(pred);
    dcsc(rem);
}

/**
 * Reads directed graph given as an edge list from STDIN.
 * Compresses the IDs of nodes to the range 0 to #n-1.
 * Constructs the adjacency list #adj (and also its transpose #rev)
 * isomorphic to the input graph.
 */
void Graph::read()
{
    Input in;
    std::string su, sv;
    std::vector<std::pair<int, int>> edges;
    while(in >> su >> sv)
    {
        int u, v;
        if(compress.count(su))
            u = compress.at(su);
        else
            u = compress[su] = int(compress.size()), decompress.push_back(su);
        if(compress.count(sv))
            v = compress.at(sv);
        else
            v = compress[sv] = int(compress.size()), decompress.push_back(sv);
        edges.push_back({u, v});
    }
    n = int(compress.size());
    node_count = n;
    edge_count = int(edges.size());
    adj.resize(node_count);
    rev.resize(node_count);
    for(auto [u, v] : edges)
        adj.at(u).push_back(v), rev.at(v).push_back(u);
}

/**
 * Function to call scc_dfs() or dcsc() according to the argument passed,
 * with the necessary parameters.
 */
void Graph::find_scc(int algo)
{
    if(algo == 0)
        scc_dfs();
    else if(algo == 1)
    {
        std::vector<int> vertices(n);
        std::iota(vertices.begin(), vertices.end(), 0);
        dcsc(vertices);
    }
}
