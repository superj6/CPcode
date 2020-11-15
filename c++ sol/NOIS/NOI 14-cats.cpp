/*
  Realize the algorithm will produce multiples of 2 * k with alternating parity until it reaches the first multiple greater than m.
After this, the parity of the 2 * k multiples greater than m make the pattern 0 1 10 1001 10010110... where the sequence gets copied
and inverted. You can find the number at the ith index using the parity of the bitcount of i. However, the algorithm will only keep back
tracking in this method until it has erased all the numbers. At that point it restarts the sequence back from i = 0 again. This means
you just have to figure out by pattern analysis how long it will be until the sequence restarts based on the multiple number of 2 * k
and output that multiple or'd with the parity of the bitcount of n - 1 mod how long the sequence is before restarting.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

ll n, m, k;

void answer(){
	cin >> n >> m >> k;
	n--, k *= 2, m = m / k + 1;
	
	ll ret = k * m++;
	ret |= __builtin_popcountll(m <= __lg(n) ? n & ((1ll << m) - 1) : n) & 1;

	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
