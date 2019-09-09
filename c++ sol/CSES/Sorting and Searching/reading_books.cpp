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
	
	long long sum = 0;
	long long a[n];
	for(int i = 0; i < n; i++){
		cin >> a[i];
		sum += a[i];
	}
	
	long long l = -1;
	
	for(int i = 0; i < n; i++) if(2 * a[i] > sum) l = a[i];
	
	if(l == -1) cout << sum << endl;
	else cout << 2 * l << endl;

	return 0;
}