#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <unordered_map>
#include <set>
using namespace std;
#define endl '\n'

const int inf = 1000000007;

struct mir{
	int x, y, r;
	bool hit[2];
};

struct line{
	int x, y, X, Y;	
	
	friend bool operator<(line a, line b){
		return make_pair(a.x, a.X) < make_pair(b.x, b.X);
	}
};

const int maxn = 100010;
int n, bx, by;
mir a[maxn];
int ind[maxn], ft[maxn];
unordered_map<int, vector<int>> b[4];

function<bool(int, int)> cmp[4] = {
	[&](int f, int g){return a[f].y < a[g].y;},
	[&](int f, int g){return a[f].x < a[g].x;},
	[&](int f, int g){return a[f].y > a[g].y;},
	[&](int f, int g){return a[f].x > a[g].x;}
};

void add(int i, int v){
	i++;
	for(; i < maxn; i += (i & -i)) ft[i] += v;
}

int qry(int i){
	i++;
	int ret = 0;
	for(; i > 0; i -= (i & -i)) ret += ft[i];
	return ret;
}

void path(int x, int y, int r, vector<line> l[2]){
	while(true){
		a[n] = (mir){x, y};
		vector<int> cur = b[r][r % 2 ? y : x];
		if(cur.size() == 0) break;
		
		auto it = upper_bound(cur.begin(), cur.end(), n, cmp[r]);
		if(it == cur.end()) break;
		
		int nx = *it;
		if(a[nx].x != bx || a[nx].y != by) l[r % 2].push_back((line){min(x, a[nx].x), min(y, a[nx].y), max(x, a[nx].x), max(y, a[nx].y)});
		
		int mr = ((r + 4 - a[nx].r) % 4 < 2);
		if(a[nx].hit[mr]) return;
		
		a[nx].hit[mr] = 1;
		x = a[nx].x;
		y = a[nx].y;
		r = (r + ((r + a[nx].r) % 2 ? 1 : 3)) % 4;
	}
	
	if(r == 0) l[r % 2].push_back((line){x, y, x, inf});
	if(r == 1) l[r % 2].push_back((line){x, y, inf, x});
	if(r == 2) l[r % 2].push_back((line){x, -inf, x, y});
	if(r == 3) l[r % 2].push_back((line){-inf, y, x, y});

}

int ans(vector<line> h, vector<line> v){
	if(h.size() == 0 || v.size() == 0) return 0;
	int ret = 0;
	set<int> pos;
	vector<int> p;
	vector<line> pts;
	
	for(int i = 0; i < h.size(); i++){
		pos.insert(h[i].y);
		pts.push_back(h[i]);
		swap(h[i].x, h[i].X);
		pts.push_back(h[i]);
	} 
	
	for(int i = 0; i < v.size(); i++){
		pts.push_back(v[i]);
	}
	
	for(auto it = pos.begin(); it != pos.end(); it++){
		p.push_back(*it);
	}
	
	sort(pts.begin(), pts.end());
	for(line cur : pts){
		int y = upper_bound(p.begin(), p.end(), cur.y) - p.begin() - 1;
		if(cur.x == cur.X){
			int Y = lower_bound(p.begin(), p.end(), cur.Y) - p.begin() - 1;
			ret += qry(Y) - qry(y);
		}else{
			add(y, (cur.x < cur.X ? 1 : -1));
		}
	}
	
	return ret;
}

int main(){
	freopen("optics.in", "r", stdin);
	freopen("optics.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> bx >> by;
	n += 2;
	
	ind[0] = 0;
	ind[1] = 1;
	a[0] = (mir){0, 0};
	a[1] = (mir){bx,by};
	a[0].hit[0] = a[0].hit[1] = 1;
	a[1].hit[0] = a[1].hit[1] = 1;
	
	for(int i = 2; i < n; i++){
		char c;
		cin >> a[i].x >> a[i].y >> c;
		a[i].r = c == '/';
		
		ind[i] = i;
	}
	
	for(int i = 0; i < 4; i++){
		sort(ind, ind + n, cmp[i]);
		
		for(int j = 0; j < n; j++){
			b[i][i % 2 ? a[ind[j]].y : a[ind[j]].x].push_back(ind[j]);
		}
	}
	
	vector<line> l1[2], l2[2];
	
	path(0, 0, 0, l1);
	for(int i = 0; i < 4; i++) path(bx, by, i, l2);
	
	cout << (ans(l1[1], l2[0]) + ans(l2[1], l1[0])) << endl;

	return 0;
}