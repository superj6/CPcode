#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
int n;

void answer(){
	cin >> n;
	
	int ret = inf;
	for(int i = 0; i * i <= n; i++){
		int z = sqrt(n - i * i);
		if(i * i + z * z == n) ret = min(ret, i + z);
	}
	
	cout << (ret < inf ? ret : -1) << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}