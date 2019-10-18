#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
int a[maxn][4];
pi b[4 * maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int j = 0; j < 2; j++){
		for(int i = 0; i < n; i++){
			cin >> a[i][j << 1 | 0] >> a[i][j << 1 | 1];
		}
	} 
	
	for(int i = 0; i < n; i++){
		b[i << 2 | 0] = {a[i][0] - a[i][3], 1};
		b[i << 2 | 1] = {a[i][0] - a[i][2] + 1, -1};
		b[i << 2 | 2] = {a[i][1] - a[i][3] + 1, -1};
		b[i << 2 | 3] = {a[i][1] - a[i][2] + 2, 1};
	}
	
	sort(b, b + 4 * n);
	
	long d = 0, t = 0, ret = 0;
	for(int i = 0; i < 4 * n - 1; i++){
		d += b[i].second;
		t += d * (b[i + 1].first - b[i].first);
		ret = max(ret, t);
	}
	
	cout << ret << endl;

	return 0;
}