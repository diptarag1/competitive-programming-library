struct smin{
    deque<pair<int,int>> d;
    int l, r;
    
    smin(){
        l = r = 0;
    }
    
    void push_back(int x){
        while(!d.empty() && d.back().first >= x) d.pop_back();
        d.emplace_back(x,r);
        ++r;
    }
    
    void pop_front(){
        if(d.front().second == l) d.pop_front();
        ++l;
    }
    
    int get_min(){
        return d.empty() ? INF : d.front().first;
    }
};
