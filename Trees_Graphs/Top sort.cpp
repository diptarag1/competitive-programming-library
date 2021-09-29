int cyc = 0;

void dfs(int node, vvi& g, vi& visited, vi& ans) {
    	if(cyc) return;
	visited[node] = 1;
	for(int i : g[node]) {
		if(visited[i] == 1) { cyc = 1; return; } 
        	if(visited[i] == 2) continue;
		dfs(i,g,visited,ans);
	}
    	visited[node] = 2;
	ans.pb(node);
}	

vector<int> topsort(vvi& g) {
	int n = g.size(); cyc = 0;
	vector<int> ans;
	vector<int> visited(n);
	loop(i,0,n) {
		if(visited[i]) continue;
		dfs(i,g,visited,ans);
	}
	reverse(ans.begin(),ans.end());
	return ans;
}
