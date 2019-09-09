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
	
	pair<int, int> a[n];
	
	for(int i = 0; i < n; i++){
		cin >> a[i].second >> a[i].first;
	}
	
	sort(a, a + n);
	
	int cnt = 0, last = -1;
	
	for(int i = 0; i < n; i++){
		if(a[i].second >= last){
			cnt++;
			last = a[i].first;
		}
	}
	
	cout << cnt << endl;

	return 0;
}