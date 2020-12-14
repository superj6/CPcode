#include <iostream>
#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 501;
int n, m, q;
bitset<mxn * mxn> a, b;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	m++;
	
	for(int i = 0; i < n; i++)
	for(int j = 1; j < m; j++){
		char c;
		cin >> c;
		a[i * m + j] = b[i * m + j] = (c == '.');
	}
	
	while(q--){
		char c;
		cin >> c;
		switch(c){
			case 'N':
				a = (a >> m) & b;
				break;
			case 'E':
				a = (a << 1) & b;
				break;
			case 'S':
				a = (a << m) & b;
				break;
			case 'W':
				a = (a >> 1) & b;
				break;
			case '?':
				a = ((a >> m) | (a << 1) | (a << m) | (a >> 1)) & b;
				break;
		}
	}
	
	cout << a.count() << endl;

	return 0;
}