#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int n = 8;
int k;
int a[n], b[n], c[2 * n], d[2 * n];


int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char x;
		cin >> x;
		if(x == '*') k++, a[i]++, b[j]++, c[i + j]++, d[i - j + n]++;
	}
	
	bool t = k == 8;
	for(int i = 0; i < n; i++) t &= !~-a[i] && !~-b[i];
	for(int i = 0; i < 2 * n; i++) t &= c[i] <= 1 && d[i] <= 1;
	
	cout << (t ? "valid" : "invalid") << endl;
	
	return 0;
}