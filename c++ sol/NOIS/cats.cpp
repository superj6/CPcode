#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

ll n, m, k;

void answer(){
	cin >> n >> m >> k;
	n--, k *= 2, m = m / k + 1;
	
	ll ret = k * m++;
	ret |= __builtin_popcountll(m <= __lg(n) ? n & ((1ll << m) - 1) : n) & 1;

	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}