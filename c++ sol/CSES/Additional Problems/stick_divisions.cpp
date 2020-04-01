#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

int n, m;
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> m >> n;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		pq.push(x);
	}
	
	long long ret = 0;
	while(pq.size() > 1){
		int c = pq.top(); pq.pop();
		c += pq.top(); pq.pop();
		ret += c;
		pq.push(c);
	}
	
	cout << ret << endl;

	return 0;
}