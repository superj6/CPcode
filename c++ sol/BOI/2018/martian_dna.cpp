#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 200000;
int n, m, k;
int a[maxn], b[maxn];
queue<int> q[maxn];
multiset<int> cur;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	for(int i = 0; i < k; i++){
		int x;
		cin >> x;
		cin >> b[x];
	}
	
	int ret = n + 1;
	for(int i = 0; i < n; i++){
		if(b[a[i]]){
			q[a[i]].push(i);
			if(q[a[i]].size() > b[a[i]]){
				cur.erase(cur.find(q[a[i]].front()));
				q[a[i]].pop();
			}
			if(q[a[i]].size() == b[a[i]]){
				cur.insert(q[a[i]].front());
			}
			if(cur.size() == k) ret = min(ret, i - *cur.begin() + 1);
		}
	}
	
	cout << (ret == n + 1 ? "impossible" : to_string(ret)) << endl;

	return 0;
}