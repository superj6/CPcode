#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const long add = 10;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	long cnt = 0;
	long amt[n];
	memset(amt, 0, sizeof(amt));
	amt[0]++;
	
	for(long i = 0, cur = 0; i < n; i++){
		int a;
		cin >> a;
		
		cur += a;
		cur %= n;
		if(cur < 0) cur += n;
		
		cnt += amt[cur];
		
		amt[cur]++;
	}
	
	cout << cnt << endl;

	return 0;
}