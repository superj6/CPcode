#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

const int maxn = 10000;
int n, m, w, h;
pi s;
pi a[maxn], b[maxn];
int ans[maxn];

bool cp(pi x, pi y){
    return x.f * y.s < x.s * y.f;
}

pi af(pi x, pi y){
    pi p = {x.f - y.f, x.s - y.s};
    return {(2 * (p.s > 0) - 1) * (abs(p.f) - p.f + abs(p.s)), abs(p.f) + abs(p.s)};
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> w >> h >> s.f >> s.s >> m;
	
	for(int i = 0; i < m; i++){
	    cin >> b[i].f >> b[i].s;
	    ans[i] = 1;
	}
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i].f >> a[i].s;
	
	int ret = m;
	for(int i = 0; i < n; i++){
	    pi p = af(s, a[i]), pa = {3, 1}, pb = {-3, 1}, pc = {3, 1}, pd = {-3, 1}, px;
	    for(int j = 0; j < n; j++){
	        if(i == j) continue;
	        px = af(a[i], a[j]);
	        if(cp(p, px) && cp(px, pa)) pa = px;
	        if(cp(px, p) && cp(pb, px)) pb = px;
	        if(cp(px, pc)) pc = px;
	        if(cp(pd, px)) pd = px;
	    }
	    for(int j = 0; j < m; j++){
	        px = af(b[j], a[i]);
	        ret -= (ans[j] - (ans[j] &= pa.f == 3 ? cp(pb, px) || cp(px, pc) :
	                                    pb.f == -3 ? cp(pd, px) || cp(px, pa) :
	                                    cp(pb, px) && cp(px, pa)));
	    }
	}
	
	cout << ret << endl;
	for(int i = 0; i < m; i++){
	    if(ans[i]){ 
	        cout << i + 1;
	        if(--ret) cout << " ";
	    }
	}
	cout << endl;

	return 0;
}