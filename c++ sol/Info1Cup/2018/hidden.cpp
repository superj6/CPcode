//#include "grader.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

const int mxn = 200;
int n;
int b[mxn];

bool isSubsequence(vi v){
	int x = 0;
	for(int i = 0; i < n && x < v.size(); i++) x += b[i] == v[x];
	return x == v.size();
}

vi findSequence(int n){
	int x = 0, m, k;
	vi a, v(n / 2 + 1, x);
	x ^= isSubsequence(v);
	
	v.assign(1, x);
	while(isSubsequence(v)) v.push_back(x);
	k = v.size() - 1;
	
	for(int i = 0; i <= k; i++){
		v[i] = !x;
		if(isSubsequence(v)) a.push_back(i);
		v[i] = x;
	}
	
	m = a.size();
	vi f, dp[2][m];
	f.resize(m);
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < m; j++){
			if(j) dp[i][j].assign(abs(a[j - 1] - i * k) + 1, x);
			for(int l = j - 1, y = 1; ~l; l--){
				if(l != j - 1) y += abs(a[l + 1] - a[l]);
				if(dp[i][l].size() + y + 1 < dp[i][j].size()){
					dp[i][j] = dp[i][l];
					dp[i][j].push_back(!x);
					v.assign(y, x);
					dp[i][j].insert(dp[i][j].end(), v.begin(), v.end());
				}
			}
		}
		reverse(a.begin(), a.end());
	}
	reverse(dp[1], dp[1] + m);
	for(int j = 0; j < m; j++) reverse(dp[1][j].begin(), dp[1][j].end());
	
	int z = 0, w = 0, c = 0;
	for(int i = 0; i < m; i++){
		f[i] = 0;
		v = dp[0][i];
		v.push_back(!x);
		v.insert(v.end(), dp[1][i].begin(), dp[1][i].end());
		
		while(v.size() <= n / 2 + 1 && isSubsequence(v)){
			f[i]++;
			v.insert(v.begin() + dp[0][i].size(), !x);
		}
		if(v.size() > n / 2 + 1){
			if(w < f[i]) w = f[i], c = 1;
			else c += w == f[i];
			f[i] *= -1;
		}else{
			z += f[i];
		} 
	}
	
	for(int i = 0; i < m; i++){
		if(f[i] < 0 && -f[i] != w) f[i] *= -1, z += f[i];
	}
	
	vi ans;
	for(int i = 0; i < m; i++){
		if(-f[i] == w) f[i] = (n - k - z) / c;
		v.assign(a[i] - (i ? a[i - 1] : 0), x);
		ans.insert(ans.end(), v.begin(), v.end());
		v.assign(f[i], !x);
		ans.insert(ans.end(), v.begin(), v.end());
	}
	v.assign(k - a.back(), x);
	ans.insert(ans.end(), v.begin(), v.end());
	
	return ans;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> b[i];
	
	vi v = findSequence(n);
	
	cout << v[0];
	for(int i = 1; i < n; i++) cout << " " << v[i];
	cout << endl;

	return 0;
}