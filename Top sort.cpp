void dfs(int node, vvi& g, vi& visited, vi& ans) {
	visited[node] = 1;
	for(int i : g[node]) {
		if(visited[i]) continue;
		dfs(i,g,visited,ans);
	}
	ans.pb(node);
}	

vector<int> topsort(vvi& g) {
	int n = g.size();
	vector<int> ans;
	vector<int> visited(n);
	loop(i,0,n) {
		if(visited[i]) continue;
		dfs(i,g,visited,ans);
	}
	reverse(ans.begin(),ans.end());
	return ans;
}