#define ll                    long long
#define loop(i,a,b)           for(int i=(int)a;i<(int)b;++i)
#define loopr(i,a,b)          for(int i=(int)a;i>=(int)b;--i)
#define count_1(n)            __builtin_popcountll(n)
#define pb                    push_back
#define vi                    vector<int>
#define vvi                   vector<vector<int>>

template<typename T> inline void debug(T a) { cout << a << endl; }
template<typename T, typename... Args> inline void debug(T a, Args... args) { cout << a << " "; debug(args...); }
