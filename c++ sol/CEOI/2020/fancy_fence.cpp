#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 100002;
int n;
ll a[mxn], b[mxn];
stack<int> stk;

ll f(ll x){
	return x * (x + 1) / 2 % mod;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++){
		 cin >> b[i];
		 (b[i] += b[i - 1]) %= mod;
	}
	
	ll ret = 0;
	stk.push(0);
	for(int i = 1, x; i <= n + 1; i++){
		while(a[x = stk.top()] > a[i]){
			stk.pop();
			(ret += (mod + f(a[x]) - f(max(a[i], a[stk.top()]))) * 
				f(mod + b[i - 1] - b[stk.top()])) %= mod;
		}
		stk.push(i);
	}
	
	cout << ret << endl;

	return 0;
}