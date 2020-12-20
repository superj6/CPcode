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

const int m = 20;
ll n, k;
ll dp[1 << m][m][2];
vector<int> v;

void answer(){
	cin >> n >> k;
	k--;
	
	int x = (1 << n) - 1, y = -1;
	v.clear();
	for(int i = 0; i < n && !~y; i++)
	for(int j = 0; j < 2 && !~y; j++){
		if(k >= dp[x][i][j]) k -= dp[x][i][j];
		else x ^= 1 << i, y = j, v.push_back(i + 1);
	}
	
	for(y ^= 1; x; y ^= 1)
	for(int i = 0; i < n; i++) if(((x >> i) & 1) && (i < v.back()) == y){
		if(k >= dp[x][i][y]){
			k -= dp[x][i][y];
		}else{
			x ^= 1 << i, v.push_back(i + 1);
			break;
		}
	}
	
	cout << v[0];
	for(int i = 1; i < n; i++) cout << " " << v[i];
	cout << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i = 0; i < m; i++)
	for(int j = 0; j < 2; j++){
		dp[1 << i][i][j] = 1;
	}
	
	for(int i = 0; i < (1 << m); i++)
	for(int j = 0; j < m; j++) if((i >> j) & 1)
	for(int l = 0; l < m; l++) if(!((i >> l) & 1)){
		dp[i | (1 << l)][l][l < j] += dp[i][j][l > j];
	}
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}