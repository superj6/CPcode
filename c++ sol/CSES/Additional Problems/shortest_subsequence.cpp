#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

unordered_map<char, int> mp;
char rmp[4] = {'A', 'C', 'G', 'T'};

const int maxn = 1000001;
int n;
string s;
bool dp[maxn][4];
int l = 1;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	mp['A'] = 0;
	mp['C'] = 1;
	mp['G'] = 2;
	mp['T'] = 3;
	
	dp[0][0] = dp[0][1] = dp[0][2] = dp[0][3] = 1;
	
	cin >> s;
	n = s.size();
	
	string ret;
	for(int i = 0; i < n; i++){
		dp[l][mp[s[i]]] = 1;
		if(dp[l][0] && dp[l][1] && dp[l][2] && dp[l][3]) l++, ret += s[i];
	}
	
	for(int i = 0; i < 4; i++){
		if(!dp[l][i]){
			cout << ret + rmp[i] << endl;
			break;
		} 
	}

	return 0;
}