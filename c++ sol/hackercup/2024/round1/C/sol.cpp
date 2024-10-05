#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 998244353;
ll n, m, k; //W, G, L

ll exp_move_left(){
  return (1 + 2 * k) % mod;
}

void answer(){
  cin >> n >> m >> k;

  ll ret = ((mod + (n - m) % mod) % mod) * exp_move_left() % mod;

  cout << ret << endl;
}

int main(){
  freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
  cout << fixed << setprecision(7);

	int t;
	cin >> t;

	for(int i = 1; i <= t; i++){
		cout << "Case #" << i << ": ";
		answer();
	}
	
	return 0;
}
