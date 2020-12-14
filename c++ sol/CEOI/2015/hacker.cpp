#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 5000001;
int n;
ll a[maxn], s[maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	
	ll ret = 0x3f3f3f3f3f3f3f3f;
	for(int t = 0; t < n; t++){
		for(int i = 1; i <= n; i++) s[i] = a[i] + s[i - 1];
		ll cur = 0;
		for(int i = 1; i <= n; i++){
			cur = max(cur, a[i] + min(s[i - 1], s[n] - s[i]));
		}
		ret = min(ret, cur);
		rotate(a + 1, a + 2, a + n + 1);
	}
	
	cout << ret << endl;

	return 0;
}