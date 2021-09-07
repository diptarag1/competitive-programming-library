vi tin(3e5, -1);
vi low(3e5, 1e7);
vvi g(3e5);

int timer = 0;

void dfs(int node, int par) {
    tin[node] = timer++; low[node] = tin[node];
    for(int i : g[node]) {
        if(tin[i] != -1 && i != par) {
            low[node] = min(low[node], tin[i]);
        }
    }
    for(int i : g[node]) {
        if(tin[i] == -1) {
            dfs(i,node);
            low[node] = min(low[node], low[i]);
        }
    }
}

void testcases(int test) {
    int n,m; cin>>n>>m;
    loop(i,0,m) {
        int x,y; cin>>x>>y; x--; y--;
        g[x].pb(y); g[y].pb(x);
    }
    dfs(0, -1);

    loop(i,0,n) {
        for(int j : g[i]) {
            if(low[j] > tin[i]) {
                bridge(i,j);
            }
        }
    }
}