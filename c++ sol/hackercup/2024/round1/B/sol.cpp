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

const int m = 10000001;
int n;
int is_subpr[m], pref_subpr[m], lp[m];
vector<int> p;

void precomp_primes(){
  for(int i = 2; i < m; i++){
    if(!lp[i]){
      lp[i] = i;
      p.push_back(i);
    }
    for(int j = 0; j < p.size() && i * p[j] < m && p[j] <= lp[i]; j++){
      lp[i * p[j]] = p[j];
    }
  }
}

void precomp_subprimes(){
  for(int i = 2; i < m; i++){
    is_subpr[i] = (i == 2 || (lp[i] == i && lp[i + 2] == i + 2)) ? 1 : 0;
    pref_subpr[i] = is_subpr[i] + pref_subpr[i - 1];
  }
}

void answer(){
  cin >> n;

  int ret = n >= 5 ? pref_subpr[n - 2] : 0;

  cout << ret << endl;
}

int main(){
  freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);

  precomp_primes();
  precomp_subprimes();

	int t;
	cin >> t;

	for(int i = 1; i <= t; i++){
		cout << "Case #" << i << ": ";
		answer();
	}
	
	return 0;
}
