#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	freopen("cbs.in", "r", stdin);
	freopen("cbs.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int k, n;
	cin >> k >> n;
	
	string s[k];
	stack<int> stk[k];
	
	for(int i = 0; i < k; i++) cin >> s[i];
	
	int ans = 0;
	int prv[k][n];
	memset(prv, -1, sizeof(prv));
	
	for(int i = 0; i < n; i++){
		int amt[n];
		memset(amt, 0, sizeof(amt));
		for(int j = 0; j < k; j++){
			if(s[j][i] == '('){
				stk[j].push(i);
			}else if(!stk[j].empty()){
				prv[j][i] = stk[j].top();
				stk[j].pop();
			}
			
			int x = prv[j][i];
			while(x > 0){
				amt[x]++;
				if(amt[x] == k) ans++;
				x = prv[j][x - 1];
			}
		}
	}
	
	cout << ans << endl;

	return 0;
}