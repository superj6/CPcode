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
	
	int a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	int out = 1;
	
	for(int i = 1; i < n; i++) if(a[i] != a[i - 1]) out++;
	
	cout << out << endl;

	return 0;
}