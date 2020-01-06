#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int m = 1000001;
int lcp[m];
vector<long long> primes;
void pgen(){
	for(int i = 2; i < m; i++){
		if(!lcp[i]){
			lcp[i] = i;
			primes.push_back(i);
		}
		for(int j = 0; j < primes.size() && primes[j] <= lcp[i] && i * primes[j] < m; j++){
			lcp[i * primes[j]] = primes[j];
		}
	}
}

const long long mod = 1000000007;
long long modpow(long long b, long long e){
	long long ret = 1;
	for(int i = 0; ((long long)1 << i) <= e; i++){
		if(((long long)1 << i) & e) ret = (ret * b) % mod;
		b = (b * b) % mod;
	}
	return ret;
}

long long solve(long long x){
	long long ret = x;
	for(long long i : primes){
		if(i > x) break;
		if(x % i == 0) ret = ret / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	
	if(x != 1) ret = ret / x * (x - 1);
	return ret % mod;
}

int main(){
	freopen("gymnasts.in", "r", stdin);
	freopen("gymnasts.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	pgen();
	
	long long n;
	cin >> n;
	
	
	long long ret = (1 + solve(n)) % mod;
	for(long long i = 2; i <= sqrt(n); i++){
		if(n % i == 0){
			ret = (ret + (((mod + modpow(2, i) - 1) % mod) * solve(n / i)) % mod) % mod;
			if(n / i != i) ret = (ret + (((mod + modpow(2, n / i) - 1) % mod) * solve(i)) % mod) % mod;
		}
	}
	
	cout << ret << endl;

	return 0;
}