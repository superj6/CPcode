#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int q;
map<ll, ll> a;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> q;
	
	while(q--){
		int t;
		cin >> t;
		if(!t){
			ll x, y;
			cin >> x >> y;
			a[x] = y;
		}else{
			ll x;
			cin >> x;
			cout << a[x] << endl;
		}
	}

	return 0;
}