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
	
	int ans = 0;
	
	for(int i = 5; i <= n; i *= 5){
		ans += n / i;
	}
	
	cout << ans << endl;

	return 0;
}