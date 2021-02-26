#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

ll n, a, b;

void answer(){
	cin >> n >> a >> b;
	a--, b--;
	n = __lg(n);
	
	ll x = 0, y = 0;
	for(int i = n - 1; ~i; i--){
		if(a >= x + (1ll << i)){
			x += (1ll << i);
		}else if(b >= y + (1ll << i)){
			y += (1ll << i);
		}else{
			cout << (1ll << i) << endl;
			return;
		}
	}
	
	cout << 1 << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}