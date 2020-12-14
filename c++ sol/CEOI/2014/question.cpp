#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int k = 10;
int n;
int x, y;

void solve1(){
	int ret = -1;
	for(int i = 0; i < k; i++, x >>= 1, y >>= 1){
		if((x ^ y) & 1){
			cout << (i + (x & 1) * k + 1) << endl;
			return;
		}
	}
	cout << -1 << endl;
}

void solve2(){
	y--;
	cout << (((x >> (y % k)) & 1) == y / k ? "yes" : "no") << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int m, t;
	
	cin >> m >> n >> t;
	
	for(int i = 0; i < t; i++){
		cin >> x >> y;
		if(m == 1) solve1();
		else solve2();
	}

	return 0;
}