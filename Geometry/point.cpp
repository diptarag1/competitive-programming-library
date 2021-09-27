struct point {
    ll x,y;
    point (ll x = 0,ll y = 0) : x(x), y(y) {}
    bool operator < (const point& a) const { return (y * a.x < x * a.y); }
    ll mags() { return x*x + y*y; }
    ll dotp(const point& a) { return (x * a.x + y * a.y); }
    ll crossp(const point& b) { return (x * a.y - y * a.x); }
    long double bangle(const point& a) {return atan2(crossp(b), dotp(b)); }
    friend point dir(point from, point to) { return {to.x - from.x, to.y - from.y}; }
};
