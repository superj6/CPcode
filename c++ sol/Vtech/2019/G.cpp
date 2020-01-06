#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<long long, int>
 
const int maxn = 20;
int n, m;
pi bd[maxn], r[maxn];
vector<pi> rl;
vector<int> ans[maxn];
long long sum;
long long sumb;
 
bool recur(int bi, int ri){
	if(ri < 0) return 1;
	
	int st = (ri < rl.size() - 1 && rl[ri].first == rl[ri + 1].first ? bi : 0);
	bool temp;

	for(int i = st; i < m; i++){
		if(bd[i].first == rl[ri].first){
			bd[i].first -= rl[ri].first;
			ans[bd[i].second].push_back(rl[ri].second + 1);
			temp = recur(i, ri - 1);
			bd[i].first += rl[ri].first;
			if(!temp) ans[bd[i].second].pop_back();

			return temp;
		}
	}
	
	for(int i = st; i < m; i++){
		if(bd[i].first - rl[ri].first >= rl[0].first){
			bd[i].first -= rl[ri].first;
			ans[bd[i].second].push_back(rl[ri].second + 1);
			temp = recur(i, ri - 1);
			bd[i].first += rl[ri].first;
			
			if(temp) return 1;
			ans[bd[i].second].pop_back();
		}
	}
	
	return 0;
}

bool solve(int x){
	rl.clear();
	sum = 0;
	for(int i = 0; i < n; i++){
		if(x & (1 << i)){
			sum += r[i].first;
			rl.push_back(r[i]);
		}
	}
	
	if(sum != sumb || !recur(0, rl.size() - 1)) return 0;
	
	for(int i = 0; i < m; i++){
		cout << ans[i].size();
		sort(ans[i].begin(), ans[i].end());
		for(int j : ans[i]) cout << " " << j;
		cout << endl;
	}
	
	return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cin >> r[i].first;
		r[i].second = i;
	}
	
	for(int i = 0; i < m; i++){
		cin >> bd[i].first;
		bd[i].second = i;
	}
	
	sort(r, r + n);
	sort(bd, bd + m);
	
	for(int i = 0; i < m; i++) sumb += bd[i].first;
	
	while(n && r[n - 1].first > bd[m - 1].first) n--;
	
	if(!n){
		cout << -1 << endl;
		return 0;
	}
	
	for(int i = 1; i < (1 << n); i++){
		if(solve(i)) return 0;
	}
	
	cout << -1 << endl;
 
	return 0;
}