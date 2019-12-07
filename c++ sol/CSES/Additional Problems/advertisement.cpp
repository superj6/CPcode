#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	long long maxv = 0;
	stack<pi> stk;
	stk.push({0, -1});
	for(int i = 0; i <= n; i++){
		long long x = 0;
		if(i < n) cin >> x;
		
		while(x < stk.top().first){
			int c = stk.top().first;
			stk.pop();
			maxv = max(maxv, c * (i - stk.top().second - 1));
		}
		
		stk.push({x, i});
	}
	
	cout << maxv << endl;

	return 0;
}