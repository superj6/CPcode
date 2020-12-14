#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 200000;
int n, m;
int a[maxn], b[maxn], c[maxn];
vector<pi> ans[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		b[--a[i]] = i;
	}
	
	for(int i = 0; i < n; i++){
		for(int j = i; a[j] != j; j = a[a[j]]){
			c[b[b[j]]] = max(c[b[j]], c[b[b[j]]]);
			ans[c[b[b[j]]]].push_back({b[b[j]], b[j]});
			m = max(m, ++c[b[b[j]]]);
			
			b[j] = b[b[j]];
			a[a[b[j]]] = b[a[b[j]]] = a[b[j]];
			a[b[j]] = j;
		}
	}
	
	cout << m << endl;
	for(int i = 0; i < m; i++){
		cout << ans[i].size() << endl;
		for(pi j : ans[i]) cout << j.f + 1 << " " << j.s + 1 << endl;
	}

	return 0;
}