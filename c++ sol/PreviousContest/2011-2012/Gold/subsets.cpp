/*
  NAME: super_j6
  LANG: C++
  PROG: subsets
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 13;
int n, m;
int a[maxn], b[maxn], sa[1 << maxn], sb[1 << maxn];
unordered_map<int, int> dpa[1 << maxn], dpb[1 << maxn];
int ret;

int main(){
	freopen("subsets.in", "r", stdin);
	freopen("subsets.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	if(n > maxn){
		m = n - maxn;
		n = maxn;
	}
	
	//
		for(int i = 0; i < n; i++) cin >> a[i];
		
		for(int i = 1; i < (1 << n); i++){
			for(int j = 0; j < n; j++){
				if(i & (1 << j)) sa[i] += a[j];
			}
			dpa[i][sa[i]] = 1;
		}
		
		for(int j = 0; j < n; j++){
			for(int i = 1; i < (1 << n); i++){
				if(i & (1 << j)){
					for(auto k : dpa[i ^ (1 << j)]){
						dpa[i][k.first] += k.second;
					}
				}
			}
		}
		
		for(int i = 1; i < (1 << n); i++){
			if(sa[i] % 2 == 0 && dpa[i].find(sa[i] / 2) != dpa[i].end()) ret++;
		}
	//
	
	//
		for(int i = 0; i < m; i++) cin >> b[i];
		
		for(int i = 1; i < (1 << m); i++){
			for(int j = 0; j < m; j++){
				if(i & (1 << j)) sb[i] += b[j];
			}
			dpb[i][sb[i]] = 1;
		}
		
		for(int j = 0; j < m; j++){
			for(int i = 1; i < (1 << m); i++){
				if(i & (1 << j)){
					for(auto k : dpb[i ^ (1 << j)]){
						dpb[i][k.first] += k.second;
					}
				}
			}
		}
		
		for(int i = 1; i < (1 << m); i++){
			if(sb[i] % 2 == 0 && dpb[i].find(sb[i] / 2) != dpb[i].end()) ret++;
		}
	//
	
	for(int i = 1; i < (1 << n); i++){
		for(int j = 1; j < (1 << m); j++){
			if(sa[i] == sb[j]){
				ret++;
			}else if((sa[i] + sb[j]) % 2 == 0){
				for(auto k : dpb[j]){
					if(dpa[i].find((sa[i] + sb[j]) / 2 - k.first) != dpa[i].end()){
						ret++;
						break;
					} 
				}
			}
		}
	}
	
	cout << ret << endl;

	return 0;
}