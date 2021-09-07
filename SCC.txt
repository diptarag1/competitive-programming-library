vector<vector<int>> g, gr, cg;
vector<bool> used;
vector<int> order, component, f;
vector<int> id;

void dfs1 (int v) {
    used[v] = true;
    for (int i=0; i<g[v].size(); ++i)
        if (!used[g[v][i]]) dfs1 (g[v][i]);
    order.push_back (v);
}

void dfs2 (int v, int par) {
    id[v] = par;
    used[v] = true;
    component.pb(v);
    for (int i=0; i<gr[v].size(); ++i)
        { if (!used[ gr[v][i]]) { dfs2 (gr[v][i], par); } } 
}

//main part
    int n,m; cin>>n>>m;
    g.resize(n); gr.resize(n); used.resize(n);
    loop(i,0,m) {
        int x,y; cin>>x>>y; x--; y--;
        g[x].pb(y); gr[y].pb(x);
    }
    used.assign (n, false);
    loop(i,0,n) if (!used[i]) dfs1 (i);
    used.assign (n, false);
    id.resize(n);
    loop(i,0,n) {
        int v = order[n-1-i];
        if (!used[v]) {
            dfs2 (v, v);
            component.clear();
        }
    }
    cg.resize(n);
    set<pair<int,int>> edges;
    loop(i,0,n) {
        for(int j : g[i]) { 
            int from = id[i]; int to = id[j];
            if(edges.find({from, to}) == edges.end()) { cg[from].pb(to); edges.insert({from,to}); }
        }
    }