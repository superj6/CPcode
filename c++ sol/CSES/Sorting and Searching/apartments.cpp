#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	int a[n], b[m];
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++) cin >> b[i];
	
	sort(a, a + n);
	sort(b, b + m);
	
	int cnt = 0;
	
	for(int i = 0, j = 0; i < n && j < m;){
		if(a[i] < b[j] - k){
			i++;
		}else if(a[i] > b[j] + k){
			j++;
		}else{
			cnt++;
			i++;
			j++;
		}
	}
	
	cout << cnt << endl;

	return 0;
}