#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, x;
	cin >> n >> x;
	
	pair<int, int> a[n];
	for(int i = 0; i < n; i++){
		cin >> a[i].first;
		a[i].second = i + 1;
	}
	
	sort(a, a + n);
	
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n && a[i].first + a[j].first < x; j++){
			int k = lower_bound(a, a + n, make_pair(x - a[i].first - a[j].first, 0)) - a;
			while(k == i || k == j) k++;
			if(k != n && a[i].first + a[j].first + a[k].first == x){
				cout << a[i].second << " " << a[j].second << " " << a[k].second << endl;
				return 0;
			}
		}
	}
	
	cout << "IMPOSSIBLE" << endl;

	return 0;
}