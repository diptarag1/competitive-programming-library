//Find rightmost element in range with value lesser than val (f = min(a,b))

int queryleft(int a, int b, int l, int r, int node, int val) {
        if (a >= l && b <= r) {
            if(tree[node] >= val) return -1;
            if(a == b) return a;
            if(tree[2*node+2] < val) return queryleft((a+b)/2 + 1,b,l,r,2*node+2,val);
            return queryleft(a,(a+b)/2,l,r,2*node+1,val);
        }
        else if (a > r || b < l || a > b) { return -1; }
        else { 
            int res = queryleft((a+b)/2 + 1,b,l,r,2*node+2,val);
            if(res != -1) return res;
            res = queryleft(a,(a+b)/2,l,r,2*node+1,val);
            return res;
        }
    }
}