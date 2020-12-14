#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 500000;
ll n, m, k, s;
pi a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> y >> x;
		s += (y *= 2 * (y > 0) - 1);
		
		a[m++] = {x, 2};
		if(y < k){
			a[m++] = {x - k, 1}, a[m++] = {x + k, 1};
			a[m++] = {x - y, -2}, a[m++] = {x + y, -2};
		}else{
			a[m++] = {x - y, -1}, a[m++] = {x + y, -1};
		}
	}
	
	sort(a, a + m);
	
	ll ret = s;
	for(ll i = 1, j = a[0].s; i < m; j += a[i++].s){
		ret = min(ret, s += j * (a[i].f - a[i - 1].f));
	}
	
	cout << ret << endl;

	return 0;
}