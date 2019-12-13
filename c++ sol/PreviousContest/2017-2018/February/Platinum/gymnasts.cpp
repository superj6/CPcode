/*
	To start out, I decided to try brute forcing small values and looking at the configurations that worked for each. Some
of the first things I noticed were that the difference between the min and max element in a configuration are always no more than
1, and every prime platform only has solutions where every stack has the same height. The prime fact should make you begin to think
about how the answer relates to the factors of N. After using the previously discovered facts to generate higher cases, specifically
the one where the difference in stack heights must be at most 1, I began to notice that given n, every configuration that worked
had a repeating pattern that was a size of a factor of n. Then I realized, if you call the lowest stack value in the configuration
x, every valid configuration is a repeating pattern of size gcd(x, n), and every possible combination of that size can be made
using values of x and x + 1. This is because when the values of x "fall over" they they will create a new configuration of stacks
of all equal height when when in cycles of gcd(x, n), and the values of x + 1 fall over so that they make cycles of equal stacks
except there is 1 extra on every value that was originally x + 1, therefore making the original configuration. This mean, for every
size less than n, you need to add to the result 2^gcd(x, n) - 1, except be careful for then x = n as u cannot use stack sizes of n + 1.
Doing this naively obviously will not work for n = 10^12, so you need to instead iterate over the factors of n and add to the result
(2^x - 1) * the number of values that have gcd x with n. To find out the numbers of values that have gcd values of x with n, you can
you can just find the totient functon value of n / x, as x can be multiplied with every value that is coprime with values less than
n / x to create numbers such that the only common prime factors are the ones in x, meaning x is the gcd for all those numbers. The
complexity of this is O(sqrt(n)log(sqrt(n))) as you need to iterate over all values less than sqrt(n) to find the factors of n
and for each factor iterate over all its factors.
*/

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
