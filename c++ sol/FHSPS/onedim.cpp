#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

const int maxn = 100000;
ll n, m;
pi a[maxn];
priority_queue<ll, vector<ll>, greater<ll>> pq;

void answer(){
	cin >> m >> n;
	
	ll ret1 = 0, ret2 = m;
	for(int i = 0; i < n; i++){
	    ll x, k;
	    cin >> x >> k;
	    a[i] = {max((ll)1, x - k), min(m, x + k)};
	}
	
	sort(a, a + n);
	
	while(!pq.empty()) pq.pop();
	for(int i = 0; i < n; i++){
	    pq.push(a[i].s);
	    while(pq.top() < a[i].f) pq.pop();
	    if(pq.size() > ret1) ret1 = pq.size(), ret2 = pq.top() - a[i].f + 1;
	    else if(pq.size() == ret1) ret2 += pq.top() - a[i].f + 1;
	}
	
	cout << ret1 << " " << ret2 << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}