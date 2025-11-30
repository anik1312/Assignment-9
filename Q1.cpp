#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// ======================= GRAPH CLASS ==========================
class Graph {
public:
    int V;
    vector<vector<int>> adj;        // adjacency list

    Graph(int v) {
        V = v;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }

    // ------------------ BFS ------------------
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neigh : adj[node]) {
                if (!visited[neigh]) {
                    visited[neigh] = true;
                    q.push(neigh);
                }
            }
        }
        cout << endl;
    }

    // ------------------ DFS ------------------
    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neigh : adj[node]) {
            if (!visited[neigh]) {
                DFSUtil(neigh, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS Traversal: ";
        DFSUtil(start, visited);
        cout << endl;
    }
};

// ======================= DISJOINT SET (UNION-FIND) ==========================
class DisjointSet {
public:
    vector<int> parent, rankv;

    DisjointSet(int n) {
        parent.resize(n);
        rankv.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSet(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv) return;

        if (rankv[pu] < rankv[pv])
            parent[pu] = pv;
        else if (rankv[pu] > rankv[pv])
            parent[pv] = pu;
        else {
            parent[pv] = pu;
            rankv[pu]++;
        }
    }
};

// ======================= EDGE STRUCTURE FOR KRUSKAL ==========================
struct Edge {
    int u, v, w;
};

bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

// ======================= KRUSKAL ALGO ==========================
void kruskalMST(int V, vector<Edge> &edges) {
    sort(edges.begin(), edges.end(), cmp);

    DisjointSet ds(V);

    int mst_weight = 0;
    cout << "Edges in MST (Kruskal):\n";

    for (auto &e : edges) {
        int pu = ds.find(e.u);
        int pv = ds.find(e.v);

        if (pu != pv) {
            cout << e.u << " - " << e.v << " (Weight: " << e.w << ")\n";
            mst_weight += e.w;
            ds.unionSet(pu, pv);
        }
    }

    cout << "Total Weight of MST = " << mst_weight << endl;
}

// ======================= MAIN ==========================
int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges;

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        g.addEdge(u, v);

        edges.push_back({u, v, w});
    }

    int start;
    cout << "Enter starting vertex for BFS & DFS: ";
    cin >> start;

    g.BFS(start);
    g.DFS(start);

    cout << "\n--- Minimum Spanning Tree (Kruskal) ---\n";
    kruskalMST(V, edges);

    return 0;
}
