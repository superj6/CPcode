#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

ll n;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	ll ret = 0;
	for(int i = 0; i < n; i++){
		ll x;
		cin >> x;
		ret += x;
	}
	
	cout << ret << endl;

	return 0;
}