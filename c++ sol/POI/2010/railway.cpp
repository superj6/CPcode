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

const int mxn = 100000, k = 3;
int n;
int a[mxn];
stack<int> stk[k];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < k; i++) stk[i].push(n + 1 + !i);
	for(int i = 0, j = 0; i < n; i++){
		int x;
		cin >> x, x--;
		for(int l = 1; l < k; l++){
			if(x < stk[l].top() && stk[l].top() < stk[a[i]].top()) a[i] = l;
		}
		if(!a[i]){
			cout << "NIE" << endl;
			return 0;
		}
		stk[a[i]].push(x);
		for(int l = 1; l < k; l++){
			if(stk[l].top() == j) stk[l].pop(), l = 0, j++;
		}
	}
	
	cout << "TAK" << endl;
	
	cout << a[0];
	for(int i = 1; i < n; i++) cout << " " << a[i];
	cout << endl;

	return 0;
}