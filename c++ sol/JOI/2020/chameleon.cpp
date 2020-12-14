#include "chameleon.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 1001, k = 4;
int n;
bool used[maxn];
vector<int> v;
vector<int> s[k];
vector<int> a[maxn], b[maxn];
 
bool bs(int x){
	if(Query(v) == v.size()) return 0;
	int l = 0, r = v.size() - 1;
	while(r - l > 1){
		int mid = (l + r) / 2;
		vector<int> v1(v.begin() + l, v.begin() + mid);
		v1.push_back(x);
		if(Query(v1) == v1.size()) l = mid;
		else r = mid;
	}
	a[x].push_back(v[l]);
	a[v[l]].push_back(x);
	v.erase(v.begin() + l);
	bs(x);
	return 1;
}
 
void Solve(int N){
	n = 2 * N;
	for(int i = 1; i <= n; i++){
		bool t[4] = {};
		for(int j = 0; j < k && a[i].size() < 3; j++){
			if(s[j].empty()) continue;
			v = s[j];
			v.push_back(i);
			t[j] = bs(i);
		}
		for(int j = 0; j < k; j++){
			if(!t[j]){
				s[j].push_back(i);
				break;
			}
		}
	}
	
	for(int i = 1; i <= n; i++){
		if(a[i].size() == 1) continue;
		for(int j = 0; j < k - 1; j++){
			v = a[i];
			v.erase(v.begin() + j);
			v.push_back(i);
			if(Query(v) == 1){
				b[i].push_back(a[i][j]);
				b[a[i][j]].push_back(i);
				break;
			}
		}
	}
	
	for(int i = 1; i <= n; i++){
		if(used[i]) continue;
		for(int j : a[i]){
			if(!count(b[i].begin(), b[i].end(), j)){
				Answer(i, j);
				used[i] = used[j] = 1;
				break;
			}
		}
	}
}