#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n, m;

void answer(){
	cin >> n >> m;
	
	int ret = (n / 3) * (m / 3) + (n % 3 > 0) * (m + 2) / 3 + (m % 3 > 0) * (n + 2) / 3 - (n % 3 > 0 && m % 3 > 0);
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}