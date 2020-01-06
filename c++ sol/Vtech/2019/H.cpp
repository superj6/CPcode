#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define pi pair<long long, int>

const int maxn = 100000;
int n, m;
long long d[maxn];
priority_queue<pi, vector<pi>, greater<pi>> pq;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	long long ret = 0;
	for(int i = 0; i < m; i++){
		long long x;
		cin >> x >> d[i];
		pq.push({x + d[i], i});
		ret = max(ret, x);
	}
	
	while(n--){
		pi c = pq.top();
		pq.pop();
		
		ret = max(ret, c.first);
		c.first += d[c.second];
		pq.push(c);
	}
	
	cout << ret << endl;

	return 0;
}