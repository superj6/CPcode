#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>
#define f first
#define s second

const int maxn = 200000;
int n;
int a[maxn], id[maxn], qry[maxn];
deque<int> v;
pi ans[maxn];

bool operator<=(pi a, pi b){
	return a.f * b.s <= b.f * a.s;
}

pi crs(int x, int y){
	pi ret = {abs(a[x] - a[y]), abs(x - y)};
	int g = __gcd(ret.f, ret.s);
	ret.f /= g, ret.s /= g;
	return ret;
}

int main(){
	freopen("falling.in", "r", stdin);
	freopen("falling.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		qry[i] = x;
		id[i] = i;
	}
	
	for(int t = 0; t < 2; t++){
		sort(id, id + n, [&](int x, int y){
			return (a[x] > a[y]) ^ t;	
		});
		v.clear();
		for(int i = 0; i < n; i++){
			int it = id[i];
			while(!v.empty() && (v.front() < it) ^ t) v.pop_front();
			while(v.size() > 1 && crs(it, v[1]) <= crs(it, v[0])) v.pop_front();
			v.push_front(it);
			
			int jt = qry[id[i]];
			if((a[jt] > a[it]) ^ t) continue;
			int l = 0, r = v.size();
			while(r - l > 1){
				int mid = (l + r) / 2;
				if((v[mid] < jt) ^ t || crs(v[mid - 1], v[mid]) <= crs(jt, v[mid])) l = mid;
				else r = mid;
			}
			ans[it] = ((jt < v[l]) ^ t ? crs(jt, v[l]) : (pi){-1, -1});
		}
	}
	
	for(int i = 0; i < n; i++){
		cout << ans[i].f;
		if(ans[i].f > 0) cout << "/" << ans[i].s;
		cout << endl;
	};

	return 0;
}