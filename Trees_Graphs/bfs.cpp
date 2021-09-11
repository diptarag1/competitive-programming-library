void solve(vvi& g, vi& d, vi& p) {
    queue<int> bfs; bfs.push(0); d[0] = 0;
    while(!bfs.empty()) {
        int node = bfs.front(); bfs.pop();
        for(int i : g[node]) {
            if(d[i] < INF) continue;
            d[i] = d[node] + 1; p[i] = node;
            bfs.push(i);
        }
    }
}
