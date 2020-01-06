#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

long long mod = 1000000007;


int main(){
	ifstream fin ("spainting.in");
	ofstream fout ("spainting.out");
	
	long long n, m, k;
	fin >> n >> m >> k;
	
	long long sum[n + 1];
	sum[0] = 0;
	
	for(int i = 1; i < k; i++){
		sum[i] = ((m * sum[i - 1]) % mod + m) % mod;
	}
	
	for(int i = k; i <= n; i++){
		sum[i] = ((m * sum[i - 1]) % mod - ((m - 1) * sum[i - k]) % mod + mod) % mod;
	}
	
	long long answer = 1;
	for(int i = 0; i < n; i++){
		answer = (answer * m) % mod;
	}
	
	long long away = (sum[n] - sum[n - 1] + mod) % mod;
	
	fout << ((answer - away + mod) % mod) << endl;

	return 0;
}