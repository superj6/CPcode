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

const int mxn = 100001, k = 3;
int n;
int a[mxn], b[mxn], f[mxn], g[mxn], bit[mxn];
stack<int> stk[k];

void add(int x, int v){
	for(x++; x <= n; x += x & -x) bit[x] = max(bit[x], v);
}

int qry(int x){
	int ret = 0;
	for(x++; x; x -= x & -x) ret = max(ret, bit[x]);
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i], a[i]--;
	
	stk[0].push(a[n] = n);
	for(int i = n - 1, j = 0; ~i; i--){
		add(a[i], i);
		f[a[i]] = qry(a[i]);
		while(a[stk[0].top()] < a[i]) stk[0].pop();
		g[a[i]] = stk[0].top();
		stk[0].push(i);
	}
	
	for(int i = 0; i < k; i++) stk[i].push(n + 1 + !i);
	for(int i = 0, j = 0; i < n; i++){
		if((stk[1].top() <= n) != (stk[2].top() <= n)){
			b[i] = 1 + (stk[2].top() <= n);
			if(a[i] > stk[b[i]].top() || f[a[i]] < g[stk[b[i]].top()]){
				b[i] = 1 + (stk[1].top() <= n);
			} 
		}else{
			for(int l = 1; l < k; l++){
				if(a[i] < stk[l].top() && stk[l].top() < stk[b[i]].top()) b[i] = l;
			}
			if(!b[i]){
				cout << "NIE" << endl;
				return 0;
			}
		}
		stk[b[i]].push(a[i]);
		for(int l = 1; l < k; l++){
			if(stk[l].top() == j) stk[l].pop(), l = 0, j++;
		}
	}
	
	cout << "TAK" << endl;
	
	cout << b[0];
	for(int i = 1; i < n; i++) cout << " " << b[i];
	cout << endl;

	return 0;
}