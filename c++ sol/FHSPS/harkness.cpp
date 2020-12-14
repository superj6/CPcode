#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <map>
#include <math.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const double eps = 1e-9;
const int maxn = 30;
int n, m;
string s[maxn];
int a[maxn], b[maxn], c[maxn], d[maxn];
map<string, int> mp;

int val(string &x){
    int i = mp[x];
    double cd = c[i] + d[i];
    return (cd > 0 ? (int)(2 * b[i] / cd + 1000 * (c[i] / cd - 0.5) + eps) : a[i]);
}

void answer(){
	cin >> n;
	
	mp.clear();
	for(int i = 0; i < n; i++){
	    cin >> s[i] >> a[i];
	    mp[s[i]] = i;
	    b[i] = c[i] = d[i] = 0;
	}
	
	cin >> m;
	
	for(int i = 0; i < m; i++){
	    string x, y;
	    char z;
	    cin >> x >> y >> z;
	    int u = mp[x], v = mp[y];
	    
	    b[u] += a[v], b[v] += a[u];
	    
	    if(z == 'W') c[u] += 2, d[v] += 2;
	    else if(z == 'L') c[v] += 2, d[u] += 2; 
	    else c[u] += 1, c[v] += 1, d[u] += 1, d[v] += 1;
	}
	
	stable_sort(s, s + n, [&](string x, string y){
	    return val(x) > val(y);
	});
	
	for(int i = 0; i < n; i++) cout << s[i] << " " << val(s[i]) << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}