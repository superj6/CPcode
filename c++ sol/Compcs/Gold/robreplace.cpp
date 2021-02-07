#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

struct mque{
	stack<pi> s1, s2;
	
	ll mx(stack<pi> &s){
		return s.empty() ? 0 : s.top().s;
	}

	void add(ll x){ 
		s1.push({x, max(x, mx(s1))});
	}
	
	void del(){
		if(s2.empty()) for(; !s1.empty(); s1.pop()) s2.push({s1.top().f, max(s1.top().f, mx(s2))});
		s2.pop();
	}
	
	ll qry(){ 
		return max(mx(s1), mx(s2));
	};
	
	bool empty(){ 
		return s1.empty() && s2.empty();
	};
};

const int mxn = 1000000;
int n, m, k;
int a[mxn];
mque q;

bool sol(int x){
	while(!q.empty()) q.del();
	for(ll i = 0, j = 0, l = 0; i < n; i++){
		j += a[i], l += a[i];
		if(i >= k) q.add(j), j -= a[i - k + 1];
		if(i >= x){
			if(l - q.qry() <= m) return 1;
			q.del(), l -= a[i - x + 1];
		}
	}
	return 0;
}

int main(){
	freopen("robreplace.in", "r", stdin);
	freopen("robreplace.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	int l = k, r = n + 1;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(sol(mid)) l = mid;
		else r = mid;
	}
	
	cout << l << endl;
	
	return 0;
}