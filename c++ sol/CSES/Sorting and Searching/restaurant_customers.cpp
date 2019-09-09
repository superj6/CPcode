#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	pair<int, int> a[2 * n];
	
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;
		
		a[i] = make_pair(x, 1);
		a[i + n] = make_pair(y, -1);
	}
	
	sort(a, a + 2 * n);
	
	int cnt = 0, maxv = 0;
	
	for(int i = 0; i < 2 * n; i++){
		cnt += a[i].second;
		
		maxv = max(cnt, maxv);
	}
	
	cout << maxv << endl;

	return 0;
}