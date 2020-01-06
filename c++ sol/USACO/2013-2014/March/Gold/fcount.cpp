#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

int n;
pair<int, int> a[501];

bool works(int c){
	for(int k = 1; k <= n - 1; k++){
		int sl = 0, sr = 0;
		
		for(int i = 0; i < (k < c ? k : k + 1); i++){
			if(i != c) sl += a[i].first;
		}
		
		for(int i = (k < c ? k : k + 1); i < n; i++){
			if(i != c) sr += min(a[i].first, k);
		}
		
		if(sl > k * (k - 1) + sr) return 0;
		if(k == n - 1 && sl % 2 == 1) return 0;
	}
	
	return 1;
}

int main(){
	freopen("fcount.in", "r", stdin);
	freopen("fcount.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	n++;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].first;
		a[i].second = i + 1;
	}
	
	sort(a, a + n, greater<pair<int, int>>());
	
	vector<int> ans;
	
	for(int i = 0; i < n; i++){
		if(works(i)) ans.push_back(a[i].second);
	}
	
	sort(ans.begin(), ans.end());
	
	cout << ans.size() << endl;
	
	for(int i = 0; i < ans.size(); i++) cout << ans[i] << endl;
	

	return 0;
}