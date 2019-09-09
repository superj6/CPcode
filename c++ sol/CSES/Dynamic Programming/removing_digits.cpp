#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int inf = 1000000007;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int a[n + 1];
	a[0] = 0;
	
	for(int i = 1; i <= n; i++){
		a[i] = inf;
		for(int j = i; j > 0; j /= 10){
			a[i] = min(a[i], a[i - j % 10] + 1);
		}
	}
	
	cout << a[n] << endl;

	return 0;
}