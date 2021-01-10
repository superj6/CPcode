#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 16, k = 3;
int n;
int a[mxn];
stack<int> stk[k];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = n - 1; ~i; i--) stk[0].push(i);
	
	cout << ((1 << n) - 1) << endl;
	for(int i = 1, j = 1; i < (1 << n); i++){
		int x = __lg(i ^ (i >> 1) ^ (i - 1) ^ ((i - 1) >> 1)), y;
		if(!x){
			y = !j ? 0 : k - 1 - ((j ^ n) & 1), (++j) %= k;
		}else{
			for(int l = 0; l < k; l++){
				if(stk[l].empty() || stk[l].top() > x) y = l;
			}
		}
		cout << (a[x] + 1) << " " << (y + 1) << endl;
		stk[a[x]].pop(), stk[a[x] = y].push(x);
	}

	return 0;
}