#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100001;
int n, m;
int a[maxn], b[maxn];

int main(){
	freopen("taxi.in", "r", stdin);
	freopen("taxi.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	ll ret = 0;
	for(int i = 0; i < n; i++){
		cin >> a[i] >> b[i];
		ret += abs(a[i] - b[i]);
	} 
	a[n] = m, b[n] = 0;
	n++;
	
	sort(a, a + n);
	sort(b, b + n);
	
	for(int i = 0; i < n; i++) ret += abs(a[i] - b[i]);
	
	cout << ret << endl;

	return 0;
}