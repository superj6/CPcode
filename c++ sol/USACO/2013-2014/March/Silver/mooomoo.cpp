#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
	ifstream fin ("mooomoo.in");
	ofstream fout ("mooomoo.out");
	
	int n, b, m = 10000001;
	fin >> n >> b;
	
	int cows[b];
	for(int i = 0; i < b; i++) fin >> cows[i];
	sort(cows, cows+b);
	
	int dp[m];
	
	dp[0] = 0;
	
	for(int i = 1; i < m; i++){
		dp[i] = m;
		for(int j = 0; j < b; j++){
			if(i - cows[j] < 0) break;
			dp[i] = min(dp[i], dp[i - cows[j]] + 1);
		}
	}
	
	int volume, amount;
	fin >> volume;
	amount = dp[volume];
	
	for(int i = 1; i < n; i++){
		if(volume > 0) volume--;
		int next;
		fin >> next;
		
		if(next >= volume){
			amount += dp[next - volume];
		}else{
			amount = m;
		}
		
		if(amount >= m) break;
		
		volume = next;
	}
	
	if(amount >= m) amount = -1;
	
	fout << amount << endl;

	return 0;
}