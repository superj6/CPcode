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
	
	long long cur = 0;

	cout << cur << endl;
	
	for(long long i = 1; i < n; i++){
		cur += i * (2 * i + 1) * (i + 1) - 8 * (i - 1);
		cout << cur << endl;
	}

	return 0;
}