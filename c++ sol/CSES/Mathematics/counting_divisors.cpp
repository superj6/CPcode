#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int m = 1000001;
int lcp[m];
vector<int> primes;

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

void answer(){
	int x;
	cin >> x;
	
	int ret = 1, cnt = 1;;
	for(int i = 0; x > 1; x /= lcp[x], cnt++){
		if(lcp[x] != i){
			ret *= cnt;
			i = lcp[x];
			cnt = 1;
		}
	}
	ret *= cnt;
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	pgen();
	
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++) answer();

	return 0;
}