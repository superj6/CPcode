#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
int a[maxn], l[maxn], r[maxn];
vector<pair<pi, int>> ret;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	memset(l, -1, sizeof(l));
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
		if(l[a[i]] == -1) l[a[i]] = i;
		r[a[i]] = i;
	}
	
	stack<int> used;
	for(int i = 0; i < n; i++){
		if(l[a[i]] == i){
			used.push(a[i]);
			ret.push_back({{l[a[i]] + 1, r[a[i]] + 1}, a[i] + 1});
		}
		if(r[a[i]] == i){
			if(used.top() == a[i]){
				used.pop();
			}else{
				cout << "IMPOSSIBLE" << endl;
				return 0;
			}
		}
	}
	
	cout << ret.size() << endl;
	for(pair<pi, int> i : ret) cout << i.first.first << " " << i.first.second << " " << i.second << endl;

	return 0;
}