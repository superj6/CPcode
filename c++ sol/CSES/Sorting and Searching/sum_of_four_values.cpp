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
			int l = 0, r = n - 1;
			
			while(l < i && r > j){
				int sum = a[i].first + a[j].first + a[l].first + a[r].first;
				if(sum == x){
					cout << a[i].second << " " << a[j].second << " " << a[l].second << " " << a[r].second << endl;
					return 0;
				}else if(sum > x){
					r--;
				}else{
					l++;
				}
				
			}
		}
	}
	
	cout << "IMPOSSIBLE" << endl;

	return 0;
}