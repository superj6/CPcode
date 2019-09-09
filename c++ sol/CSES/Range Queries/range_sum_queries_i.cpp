#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	long s[n + 1];
	s[0] = 0;
	for(int i = 1; i <= n; i++){
		cin >> s[i];
		s[i] += s[i - 1];
	}
	
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		cout << s[b] - s[a - 1] << endl;;
	}

	return 0;
}