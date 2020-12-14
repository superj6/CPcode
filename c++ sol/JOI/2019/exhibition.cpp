#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100000;
int n, m;
pi a[maxn];
int b[maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i].s >> a[i].f;
	for(int i = 0; i < m; i++) cin >> b[i];
	
	sort(a, a + n, greater<pi>());
	sort(b, b + m, greater<int>());
	
	int ret = 0;
	for(int i = 0; i < n; i++){
	    if(ret < m && a[i].s <= b[ret]) ret++;
	}
	
	cout << ret << endl;

	return 0;
}