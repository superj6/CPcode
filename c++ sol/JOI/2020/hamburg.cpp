#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int inf = 1000000007;
const int maxn = 200000;
int n, k;
int x[maxn], X[maxn], y[maxn], Y[maxn];
vector<int> a;

vector<pi> solve(vector<int> v, int z){
	if(!z && !v.empty()) return vector<pi>(1, {0, 0});
	if(v.empty()) return vector<pi>(1, {-1, -1});
	
	int mn = inf;
	for(int i : v) mn = min(mn, X[i]);
	
	vector<pi> p;
	for(int i : v){
		p.push_back({y[i], i});
		p.push_back({Y[i], i});
	}
	sort(p.begin(), p.end());

	for(int t = 0; t < 2; t++){
		bool f = 0;
		set<int> cur;
		for(pi i : p){
			f |= X[i.s] == mn;
			if(cur.find(i.s) == cur.end()){
				cur.insert(i.s);
			}else{
				if(f){
					vector<int> nv;
					for(int j : v){
						if(x[j] > mn || y[j] > i.f || Y[j] < i.f) nv.push_back(j);
					}
					vector<pi> ans = solve(nv, z - 1);
					if(ans[0].f){
						ans.push_back({mn, i.f});
						return ans;
					}
					break;
				}else{
					cur.erase(i.s);
				}
			}
		}
		reverse(p.begin(), p.end());
	}
	
	return vector<pi>(1, {0, 0});
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	a.resize(n);
	for(int i = 0; i < n; i++){
		cin >> x[i] >> y[i] >> X[i] >> Y[i];
		a[i] = i;
	}
	
	vector<pi> ans = solve(a, k);
	
	for(int i = 1; i <= k; i++){
		if(i < ans.size()) cout << ans[i].f << " " << ans[i].s << endl;
		else cout << 69 << " " << 420 << endl;
	} 

	return 0;
}