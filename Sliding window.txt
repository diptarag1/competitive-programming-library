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
        return d.empty() ? 1e15 : d.front().first;
    }
};

struct smax{
    deque<pair<int,int>> d;
    int l, r;
    
    smax(){
        l = r = 0;
    }
    
    void push_back(int x){
        while(!d.empty() && d.back().first <= x) d.pop_back();
        d.emplace_back(x,r);
        ++r;
    }
    
    void pop_front(){
        if(d.front().second == l) d.pop_front();
        ++l;
    }
    
    int get_max(){
        return d.empty() ? 0 : d.front().first;
    }
};