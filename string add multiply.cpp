string add(string& a, string& b) {
    if(b.size() > a.size()) swap(a,b);
    reverse(b.begin(), b.end());
    while(b.size() < a.size()) b += '0';
    reverse(b.begin(), b.end());
    string ans; int carry = 0;
    loopr(i,a.size()-1,0) {
        int cur = (a[i] - '0' + b[i] - '0' + carry);
        carry = cur/10; cur%=10;
        ans += (cur + '0');
    }
    if(carry) ans += (carry + '0');
    reverse(ans.begin(), ans.end());
    return ans;
}

string multiply(string& a, string& b) {
    if(a.compare("0") == 0 || b.compare("0") == 0) return "0";
    string ans = "0";
    loopr(i,b.size() - 1,0) {
        string tans = a; if(b[i] == '0') tans = "0";
        loop(j,0,b[i]-'1') { tans = add(tans, a); }
        loop(j,0,b.size()-1-i) tans += '0';
        ans = add(ans, tans);
    }
    return ans;
}