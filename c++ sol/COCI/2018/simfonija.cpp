#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100001;
int n, k;
ll a[mxn], s[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		a[i] -= x;
	}
	
	sort(a + 1, a + n + 1);
	
	for(int i = 1; i <= n; i++)  s[i] = a[i] + s[i - 1];
	
	ll ret = 0x3f3f3f3f3f3f3f3f;
	for(int i = 1, j = 0; i <= n; i++){
		while(j < k && a[i] - a[j + 1] >= a[n - k + j + 1] - a[i]) j++;
		ret = min(ret, 
			a[i] * ((i - j) - (n - k + j - i)) +
			(s[n - k + j] - s[i]) - (s[i] - s[j])
		);
	}
	
	cout << ret << endl;
	
	return 0;
}