void solve(vector<vector<pair<int,ll>>>& g, vector<ll>& d, vector<int>& p, int s) {
    int n = g.size();
    priority_queue<pair<ll,int> , vector<pair<ll,int>>, greater<pair<ll,int>>> dijkstra;
    d[s] = 0; dijkstra.push({d[s],s});

    while(!dijkstra.empty()) {
        auto [l, node] = dijkstra.top(); dijkstra.pop();
        if(l != d[node]) continue;
        for(auto [to, len] : g[node]) {
            if(d[node] + len < d[to]) {
                d[to] = d[node] + len;
                p[to] = node;
                dijkstra.push({d[to],to});
            }
        }
    }
}
