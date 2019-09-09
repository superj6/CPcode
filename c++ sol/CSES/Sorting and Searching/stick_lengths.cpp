#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long n;
	cin >> n;
	
	long long a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	
	long long out = 0, sub = a[n / 2];
	for(int i = 0; i < n; i++) out += abs(a[i] - sub);
	
	cout << out << endl;

	return 0;
}