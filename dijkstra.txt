loop(i,0,300000) d[i] = 1e15;
    int n,m; cin >>n >> m;
    vector<vector<pair<int,int>>> g(n);
    loop(i,0,m) {
        int x,y,z; cin >> x >> y >> z;
        x--; y--;
        g[x].pb({y,z});
    }
    set<pair<int,int>> q;
    q.insert({0,0});
    d[0] = 0;
 
    while(!q.empty()) {
        int v = q.begin()->second; q.erase(q.begin());
        for(pair<int,int> i : g[v]) {
            int to = i.first;
            int len = i.second;
 
            if(d[v] + len < d[to]) {
                set<pair<int,int>>::iterator itr = q.find({d[to],to});
                if(itr != q.end()) q.erase(itr);
                d[to] = d[v] + len;
                q.insert({d[to], to});
            }
        }
    }