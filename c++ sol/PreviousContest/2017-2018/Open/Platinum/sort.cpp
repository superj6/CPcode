#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
pi a[maxn];
int p[maxn];
long ret;

int main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].first;
		a[i].second = i;
	}
	
	sort(a, a + n);
	
	for(int i = 0, j = 0; i < n; i++){
		j = max(j, a[i].second);
		p[i] = j - i;
		ret += max((n > 1 ? 1 : 0), max(p[i], (i > 0 ? p[i - 1] : 0)));
	}
	
	cout << ret << endl;
	
	return 0;
}