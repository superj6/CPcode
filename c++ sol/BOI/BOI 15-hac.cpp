/*
  Realize that if you start at a given location, the operator can always force you onto the smallest range of ceil(n / 2) values.
This means you should compute prefix sums and hold ceil(n / 2) consecutive ranges in a queue that can store the minimum, and just
push and pop values from the queue to test all starting starting points and find the largest minimum sum of ceil(n / 2) values.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second
 
struct mque{
	stack<pi> s1, s2;
	
	ll mn(stack<pi> &s){
		return s.empty() ? 0x3f3f3f3f3f3f3f3f : s.top().s;
	}
	
	void add(ll x){
		s1.push({x, min(x, mn(s1))});
	}
	
	void del(){
		if(s2.empty()) for(; !s1.empty(); s1.pop()) s2.push({s1.top().f, min(s1.top().f, mn(s2))});
		s2.pop();
	}
	
	ll qry(){
		return min(mn(s1), mn(s2));
	}
};
 
const int mxn = 1500001;
int n;
ll a[mxn];
mque q;
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		for(int j = 1; j < 3; j++) a[j * n + i] = a[i];
		a[i] += a[i - 1];
	}
	
	ll ret = 0;
	for(int i = n + 1; i <= 3 * n; i++){
		a[i] += a[i - 1];
		q.add(a[i] - a[i - (n + 1) / 2]);
		if(i - n > (n + 1) / 2) q.del(), ret = max(ret, q.qry());
	}
	
	cout << ret << endl;
 
	return 0;
}
