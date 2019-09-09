#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define endl '\n'

const long add = 10;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	long x;
	cin >> n >> x;
	
	long cnt = 0;
	unordered_map<long, long> amt;
	amt[0]++;
	
	for(long i = 0, cur = 0; i < n; i++){
		int a;
		cin >> a;
		cur += a;
		
		cnt += amt[cur - x];
		
		amt[cur]++;
	}
	
	cout << cnt << endl;

	return 0;
}