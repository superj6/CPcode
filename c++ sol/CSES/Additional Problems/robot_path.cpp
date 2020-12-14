#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
const int maxn = 1 << 18;
 
struct MBIT{
	set<int> bit1[2][maxn], bit2[2][maxn];
	 
	void add(set<int> bit[2][maxn], int x, int v){
		if(v < 0) bit[0][x].erase(-v);
		else bit[0][x].insert(v);
		for(; x < maxn; x += x & -x){
			if(v < 0) bit[1][x].erase(-v);
			else bit[1][x].insert(v);
		}
	}
	 
	void add(int x, int v){
		x++;
		add(bit1, x, v);
		add(bit2, maxn - x, v);
	}
	 
	int qry(set<int> bit[2][maxn], int x, int y, int z){
		int ret = inf;
		for(; x <= y - (y & -y); y -= y & -y){
			auto it = bit[1][y].lower_bound(z);
			if(it != bit[1][y].end()) ret = min(ret, *it);
		}
		auto it = bit[0][y].lower_bound(z);
		if(it != bit[0][y].end()) ret = min(ret, *it);
		return ret;
	}
	 
	int qry(int x, int y, int z){
		x++, y++;
		int ret = inf;
		ret = min(ret, qry(bit1, x, y, z));
		ret = min(ret, qry(bit2, maxn - y, maxn - x, z));
		return ret;
	}
};

int n;
long long px[maxn], py[maxn], x[maxn], y[maxn], X[maxn], Y[maxn];
vector<long long> a, id(1, 0);
MBIT bit;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++){
		char c;
		int z;
		cin >> c >> z;
		px[i] = px[i - 1], py[i] = py[i - 1];
		switch(c){
			case 'U': py[i] += z; break;
			case 'R': px[i] += z; break;
			case 'D': py[i] -= z; break;
			case 'L': px[i] -= z; break;
		}
		id.push_back(px[i]), id.push_back(py[i]);
	}
	sort(id.begin(), id.end());
	id.erase(unique(id.begin(), id.end()), id.end());
	for(int i = 0; i <= n; i++){
		x[i + 1] = X[i] = lower_bound(id.begin(), id.end(), px[i]) - id.begin();
		y[i + 1] = Y[i] = lower_bound(id.begin(), id.end(), py[i]) - id.begin();
		if(x[i] > X[i]) swap(x[i], X[i]);
		if(y[i] > Y[i]) swap(y[i], Y[i]);
	}
	
	pi ans = {inf, inf};
	for(int t = 0; t < 2; t++){
		a.clear();
		for(int i = 1; i <= n; i++){
			a.push_back(i);
			if(x[i] != X[i]) a.push_back(-i);
		}
		sort(a.begin(), a.end(), [&](int f, int g){
			return (f < 0 ? (pi){X[-f], 2} : (pi){x[f], y[f] != Y[f]}) < (g < 0 ? (pi){X[-g], 2} : (pi){x[g], y[g] != Y[g]});
		});
		for(int i : a){
			int j = abs(i);
			if(y[j] == Y[j]) bit.add(y[j], i);
			int c = bit.qry(y[j], Y[j], j + 2);
			if(c < inf) ans = min(ans, {c, min(abs(px[j] - px[c - 1]), abs(px[j - 1] - px[c - 1]))});
		}
		for(int i = 1; i <= n; i++){
			swap(x[i], y[i]);
			swap(X[i], Y[i]);
			swap(px[i], py[i]);
		}
	}
	
	long long ret = 0;
	for(int i = 1; i <= n; i++){
		if(i > 1 && px[i] == px[i - 1] && px[i] == px[i - 2] && (py[i] - py[i - 1] > 0) != (py[i - 1] - py[i - 2] > 0)) break;
		if(i > 1 && py[i] == py[i - 1] && py[i] == py[i - 2] && (px[i] - px[i - 1] > 0) != (px[i - 1] - px[i - 2] > 0)) break;
		if(i == ans.f){
			ret += ans.s;
			break;
		}
		ret += abs(px[i] - px[i - 1]) + abs(py[i] - py[i - 1]);
	}
	
	cout << ret << endl;

	return 0;
}