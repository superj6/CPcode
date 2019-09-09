#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
using namespace std;
 
const int maxn = 50;
string a, b;
long long dp[maxn][2][maxn][2];
long long getdp(string s, int n, int tar1, int tar2){
	memset(dp, 0, sizeof(dp));
	dp[0][false][25][true] = 1;
	
	for(int i = 0; i < n; i++)
	for(int und = 0; und < 2; und++)
	for(int k = 0; k < maxn; k++)
	for(int is0 = 0; is0 < 2; is0++){
		long long curr = dp[i][und][k][is0];
		
		for(int nxt = 0; nxt <= 9; nxt++){
			if(tar2 != -1 && nxt != tar1 && nxt != tar2 && (nxt != 0 || is0 == false)) continue;
			if(und == 0 && nxt > s[i] - '0') continue;
			
			int nj = und | (nxt < s[i] - '0');
			bool nis0 = is0 & !nxt;
			int nk = k;
			
			if(!nis0){
				if(tar2 == -1){
					if(tar1 == nxt) nk--;
					else nk++;
				}else{
					if(tar1 == nxt) nk--;
					else if(tar2 == nxt) nk++;
				}
			}
			
			dp[i + 1][nj][nk][nis0] += curr;
		}
	}
	
	long long out = 0;
	
	if(tar2 != -1){
		for(int i = 0; i < 2; i++) out += dp[n][i][25][false];
	}else{
		for(int i = 0; i < 2; i++) for(int k = 0; k <= 25; k++) out += dp[n][i][k][false];
	}
	
	return out;
}

long long f(string s){
	int n = s.size();
	long long result = 0;
	
	for(int i = 0; i <= 9; i++){
		result += getdp(s, n, i, -1);
	}
	
	for(int i = 0; i <= 9; i++){
		for(int j = i + 1; j <= 9; j++){
			result -= getdp(s, n, i, j);
		}
	}
	
	return result;
}

int main(){
	ifstream fin ("odometer.in");
	ofstream fout ("odometer.out");

	fin >> a >> b;
	
	for(int i = a.size() - 1; i >= 0; i--){
		int c = a[i] - '0';
		if(c > 0){
			a[i]--;
			break;
		}
		else a[i] = '9';
	}
	
	fout << (f(b) - f(a)) << endl;;

	return 0;
}