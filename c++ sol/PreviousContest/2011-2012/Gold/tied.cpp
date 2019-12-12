/*
  NAME: super_j6
  LANG: C++
  PROG: tied
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>
#define x first
#define y second

long long cp(pi a, pi b, pi c){
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

const int maxn = 11, maxm = 10001;
int n, m, bx, by;
pi a[maxm], p[maxn];
vector<int> s;

int main(){
	freopen("tied.in", "r", stdin);
	freopen("tied.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> bx >> by;
	
	for(int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;
	
	sort(p + 1, p + n + 1);
	
	cin >> a[0].x >> a[0].y;
	for(int i = 1; i <= m; i++){
		cin >> a[i].x >> a[i].y;
		
		if(a[i - 1].y < a[i].y){
			for(int j = 1; j <= n; j++){
				if(cp(a[i - 1], a[i], p[j]) < 0 && 
				a[i - 1].y <= p[j].y && p[j].y < a[i].y) s.push_back(j);
			}
		}else{
			for(int j = n; j >= 1; j--){
				if(cp(a[i - 1], a[i], p[j]) > 0 && 
				a[i - 1].y > p[j].y && p[j].y >= a[i].y) s.push_back(-j);
			}
		}
	}
	
	int ret = n;
	for(int i = 0; i < (1 << n); i++){
		stack<int> stk;
		for(int j = 0; j < s.size(); j++){
			if(i & (1 << (abs(s[j]) - 1))) continue;
			if(stk.empty() || stk.top() + s[j]) stk.push(s[j]);
			else stk.pop();
		}
		if(stk.empty()) ret = min(ret, __builtin_popcount(i));
	}
	
	cout << ret << endl;

	return 0;
}