#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < (1 << n); i++){
		int x = i ^ (i >> 1);
		for(int j = n - 1; ~j; j--) cout << ((x >> j) & 1);
		cout << endl;
	}

	return 0;
}