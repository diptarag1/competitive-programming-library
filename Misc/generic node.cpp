struct point{
    int x,y,z;
    bool operator<(const point& b) const {
        if(x == b.x) {
            if(y == b.y) {
                return (z < b.z);
            }
            return (y < b.y);
        }
        return (x < b.x);
    } 
};