#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100, k = 10;
int n;
int a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		char c;
		cin >> c;
		a[n - i - 1] = c == 'x' ? -1 : c - '0';
	}
	
	int s = 0, x = find(a, a + n, -1) - a;
	for(int i = 1; i < n; i++){
		int v = (1 + (i & 1)) * a[i];
		if(i != x) s += v % 10 + v / 10;
	}
	
	if(!x){
		cout << (s * 9 % k) << endl;
	}else{
		for(int i = 0; i < k; i++){
			int v = (1 + (x & 1)) * i;
			if((s + v % 10 + v / 10) * 9 % k == a[0]){
				cout << i << endl;
				break;
			}
		}
	}

	return 0;
}