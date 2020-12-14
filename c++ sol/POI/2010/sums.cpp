#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
const int mxn = 5000, mxm = 50001;
int n, m, q;
int a[mxn];
int d[mxm];
set<pi> pq;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	m = a[0];
	
	memset(d, inf, sizeof(d));
	d[0] = 0;
	pq.insert({d[0], 0});
	while(!pq.empty()){
		int c = pq.begin()->s;
		pq.erase(pq.begin());
		for(int i = 1; i < n; i++){
			int v = (c + a[i]) % m;
			if(d[v] > d[c] + a[i]){
				pq.erase({d[v], v});
				d[v] = d[c] + a[i];
				pq.insert({d[v], v});
			}
		}
	}
	
	cin >> q;
	
	while(q--){
		int x;
		cin >> x;
		cout << (x >= d[x % m] ? "TAK" : "NIE") << endl;
	}

	return 0;
}