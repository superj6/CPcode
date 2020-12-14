#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 7501;

struct par{
		int l;
		int p[maxn];
		
		par(int x){
			memset(p, 0, sizeof(p));
			p[0] = x;
			l = 1;
		}
		
		int get(int x){
			return p[x];
		}
		
		bool works(){
			return p[0] != 0;	
		}
		
		void nxt(){
			if(p[0] == 1){
				p[0] = 0;
				return;
			}
			
			int c = 0;
			while(p[l - 1] == 1){
				c++;
				l--;	
			} 
			
			c++;
			p[l - 1]--;
			for(; c > 0; l++){
				p[l] = min(p[l - 1], c);
				c -= p[l];
			}
		}
};

int n, m;
int a[maxn], b[maxn], B[maxn];
long long f[maxn];

int lcp[maxn];
vector<int> primes;
void pgen(){
	lcp[1] = 1;
	for(int i = 2; i <= n; i++){
		if(!lcp[i]){
			lcp[i] = i;
			primes.push_back(i);
		}
		for(int j = 0; j < primes.size() && primes[j] <= lcp[i] && i * primes[j] <= n; j++){
			lcp[i * primes[j]] = primes[j];
		}
	}
}

long long modpow(long long b, int e, int m = ::m){
	long long ret = 1;
	for(int i = 0; (1 << i) <= e; i++){
		if((1 << i) & e) ret = (ret * b) % m;
		b = (b * b) % m;
	}
	return ret;
}

void init(){
	for(int i = 1; i <= n; i++){
		for(int k = i, c = 1; k > 1; k /= lcp[k], c++){
			if(lcp[k / lcp[k]] != lcp[k]){
				B[lcp[k]] += c;
				c = 0;
			}
		}
	}
}

int main(){
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	pgen();
	init();
	
	long long ret = 1;
	for(par x(n); x.works(); x.nxt()){
		memset(a, 0, (x.get(0) + 1) * sizeof(int));
		memcpy(b, B, (n + 1) * sizeof(int));
		for(int i = 0, j = 1; i < x.l; i++, j++){
			//cout << x.get(i) << " ";
			
			for(int k = j, c = 1; k > 1; k /= lcp[k], c++){
				if(lcp[k / lcp[k]] != lcp[k]){
					b[lcp[k]] -= c;
					c = 0;
				}
			}
			for(int k = x.get(i), c = 1; k > 1; k /= lcp[k], c++){
				if(lcp[k / lcp[k]] != lcp[k]){
					b[lcp[k]] -= c;
					c = 0;
				}
			}
			
			if(i == x.l - 1 || x.get(i) != x.get(i + 1)){
				j = 0;
				for(int k = x.get(i), c = 1; k > 1; k /= lcp[k], c++){
					if(lcp[k / lcp[k]] != lcp[k]){
						a[lcp[k]] = max(a[lcp[k]], c);
						c = 0;
					}
				}
			}
		}
		//cout << endl;
		
		long long cur = 1, cur2 = 1;
		for(int i = 1; i <= x.get(0); i++){
			if(a[i]) cur *= modpow(i, a[i]);
			cur %= m;
		}
		for(int i = 1; i <= n; i++){
			if(b[i]) cur2 *= modpow(i, b[i], m - 1);
			cur2 %= m - 1;
		}
		
		//cout << cur << " " << cur2 << endl;
		//cout << endl;
		
		ret *= modpow(cur, cur2);
		ret %= m;
	}
	
	cout << ret << endl;

	return 0;
}