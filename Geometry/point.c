struct point {
    ll x,y;
    point (ll x = 0,ll y = 0) : x(x), y(y) {}
    bool operator < (const point& a) const {
        return (y * a.x < x * a.y);
    }
    ll mags() {
        return x*x + y*y; 
    }
    friend point dir(point from, point to) {
        return {to.x - from.x, to.y - from.y};
    }
    friend ll dotp(const point& a, const point& b) {
        return (a.x * b.x + a.y * b.y);
    }
    friend ll crossp(const point& a, const point& b) {
        return (a.x * b.y - a.y * b.x);
    }
    friend long double bangle(point& a, point& b) {
        return atan2(crossp(a, b), dotp(a, b));
    }
};
