#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1000;
int n, m;
int a[maxn];
stack<int> stk;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	int ret = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			char c;
			cin >> c;
			a[j] = (c == '.') * (1 + a[j]);
			
			while(!stk.empty() && a[j] <= a[stk.top()]){
				int c = stk.top();
				stk.pop();
				ret = max(ret, (j - (stk.empty() ? -1 : stk.top()) - 1) * a[c]);
			}
			stk.push(j);
		}
		
		while(!stk.empty()){
			int c = stk.top();
			stk.pop();
			ret = max(ret, (m - (stk.empty() ? -1 : stk.top()) - 1) * a[c]);
		}
	}
	
	cout << ret << endl;
	
	return 0;
}