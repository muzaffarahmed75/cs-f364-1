import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
from os.path import splitext


options = {
    "node_size": 20,
    "width": 0.25,
    "font_size": 10,
    "alpha": 0.6,
    "edge_color": "#000000",
}

G = nx.DiGraph()
graph_file = input("filename: ")
with open("data/" + graph_file, "r") as content_file:
    while True:
        line = content_file.readline()
        if not line:
            break
        if line[0] == '#':
            continue
        u, v = line.split()
        G.add_edge(u, v)
    content_file.close()

shape = nx.spring_layout(G, seed=10)
nx.draw(G, pos=shape, **options)
plt.show()


G_scc = nx.DiGraph()
colors = np.array([])
stem = splitext(graph_file)[0]
with open("output/" + stem + ".dcsc.out.txt", "r") as content_file:
    # read first line as dummy
    content_file.readline()
    while True:
        line = content_file.readline()
        if line == "\n": break
        sz, vertices = line.split(": ")
        vertices = [node for node in vertices.strip().split()]
        subgraph = G.subgraph(vertices)
        colors = np.append(colors, np.ones((int(sz), )) * np.random.randint(255))
        G_scc = nx.union(G_scc, subgraph)
    content_file.close()

shape = nx.spring_layout(G_scc, seed=10)
nx.draw(G_scc, pos=shape, cmap="jet", node_color=colors, **options)
plt.show()
