#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 3000000;
int n, m, q;
vector<pi> pt, qry;
int par[maxn], crd[maxn];
bool used[maxn];
vector<int> val;
vector<vector<int>> st;
vector<pi> ans;
 
void init(){
	val.clear(), st.clear();
}
 
int add(int x, int id){
	int nid = val.size();
	val.push_back(x);
	st.push_back({});
	if(id >= 0){
		par[id] = nid;
		st[nid].push_back(id);
	}
	return nid;
}
 
int unionf(int x, int y){
	if(x == y) return x;
	if(st[x].size() < st[y].size()) swap(x, y);
	val[x] = max(val[x], val[y]);
	for(int i : st[y]){
		par[i] = x;
		st[x].push_back(i);
	}
	return x;
}
 
pi gtpt(int x){
	return {val[par[2 * x]], val[par[2 * x + 1]]};
}
 
void solve(int x, int y, vector<pi> qry){
	if(qry.empty()) return;
	
	if(x + y == n){
		for(pi qr : qry){
			if(qr.f == 1) ans[qr.s] = pt[ans[qr.s].f];
		}
		return;
	}
	
	int X = x + (n - x - y) / 2 + 1, Y = n + 1 - X;
	vector<pi> qup, qrt;
	init();
	priority_queue<pi, vector<pi>, greater<pi>> xq, yq;
	for(pi qr : qry){
		 if(qr.f == 1){
		 	int i = ans[qr.s].f;
		 	if(pt[i].f >= X) qrt.push_back(qr);
		 	else if(pt[i].s >= Y) qup.push_back(qr);
		 	else{
		 		ans[qr.s] = gtpt(i);
		 	}
		 }
		 if(qr.f == 2){
		 	if(qr.s >= Y){
		 		int nx = n - qr.s;
		 		int cid = add(nx, -1);
		 		while(!xq.empty() && xq.top().f < nx){
		 			cid = unionf(cid, xq.top().s);
		 			xq.pop();
		 		}
		 		xq.push({nx, cid});
		 		qup.push_back(qr);
		 	}else{
		 		while(!yq.empty() && yq.top().f <= qr.s){
		 			for(int i : st[yq.top().s]){
		 				i /= 2;
		 				if(!used[i]){
		 					pt[i] = gtpt(i);
		 					pt[i].f = n - qr.s;
		 					qrt.push_back({4, i});
		 					used[i] = 1;
		 				}
		 			}
		 			yq.pop();
		 		}
		 		qrt.push_back(qr);
		 	}
		 }
		 if(qr.f == 3){
		 	if(qr.s >= X){
		 		int ny = n - qr.s;
		 		int cid = add(ny, -1);
		 		while(!yq.empty() && yq.top().f < ny){
		 			cid = unionf(cid, yq.top().s);
		 			yq.pop();
		 		}
		 		yq.push({ny, cid});
		 		qrt.push_back(qr);
		 	}else{
		 		while(!xq.empty() && xq.top().f <= qr.s){
		 			for(int i : st[xq.top().s]){
		 				i /= 2;
		 				if(!used[i]){
		 					pt[i] = gtpt(i);
		 					pt[i].s = n - qr.s;
		 					qup.push_back({4, i});
		 					used[i] = 1;
		 				}
		 			}
		 			xq.pop();
		 		}
		 		qup.push_back(qr);
		 	}
		 }
		 if(qr.f == 4){
		 	used[qr.s] = 0;
		 	int x = pt[qr.s].f, y = pt[qr.s].s;
		 	if(x >= X) used[qr.s] = 1, qrt.push_back(qr);
		 	else if(y >= Y) used[qr.s] = 1, qup.push_back(qr);
		 	else{
		 		int xid = add(x, 2 * qr.s);
		 		int yid = add(y, 2 * qr.s + 1);
		 		xq.push({x, xid});
		 		yq.push({y, yid});
		 	}
		 }
	}
	solve(X, y, qrt), solve(x, Y, qup);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> q;
	
	for(int i = 0; i < m + q; i++){
		int t;
		if(i < m) t = 4;
		else cin >> t;
		if(t == 1){
			int x;
			cin >> x;
			x--;
			qry.push_back({t, ans.size()});
			ans.push_back({x, -1});
		}else if(t < 4){
			int x;
			cin >> x;
			qry.push_back({t, x});
		}else{
			int x, y;
			cin >> x >> y;
			qry.push_back({t, pt.size()});
			pt.push_back({x, y});
		}
	}
	
	solve(0, 0, qry);
	
	for(pi i : ans) cout << i.f << " " << i.s << endl;
 
	return 0;
}