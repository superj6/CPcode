#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'
#define ll long long
#define ld long double
#define pi pair<int, int>
#define f first
#define s second

int n;

void answer(){
	cin >> n;
	
	ld ret = 1;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		ret *= 1 + x / 100.0;
	}
	
	cout << (ret * 100 - 100) << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(3);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}