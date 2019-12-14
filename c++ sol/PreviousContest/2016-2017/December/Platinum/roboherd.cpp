/*
	This problem is challenging as it is not obvious how the input can be used to constrain the minimum cost in a good runtime. Often
in such a case when you are trying to minimize something you end up binary searching on what you are minimizing. However, it is not helpful
in this situation as given an upper bound total cost does not help you figure out if it is possible. The key insight is the semi obvious
fact that every combination is possible and no possible combination prohibits another from being used, as this means you want to use the
robots with the k smallest prices. This means you can binary search on the upper bound cost you will use for any configuration you will use,
and see if it is possible to make at least k configurations with that budget per configuration. This is useful because the result is then
just the m * k where m is the lowest amount where at least k configurations can be made minus the sum of the amount left over per configuration
when having a budget of m - 1. This is because you know having a budget of m - 1 does not work but m does so you need the remaining cows
amount of cows required after using all configurations with budget m - 1 to be cost m. Now to calculate the cost, for each location sort
the values and set the lowest value per location to be part of the "base price". Now change the remaining prices to be the value minus
the base price. This is because you want to compare which transitions will be as cheap as possible rather than the prices themselves. Now
to see if at least k cows can be made given a budget, you can hold the budget available and for each location recurse on every transition
that works where the budget will still be greater than 0 and go to the next location. However, this will still not fall in the runtime. To
make it faster, sort the locations by the smallest transition in each location, and when you are recursing you can binary search on where
the next location it is possible to use transitions is, as you do not waste time recurring through locations where no transitions work. Also,
you must be sure to stop the recursion as soon as at least k cows have been created. The runtime is something like O(nlognlogP) where P is
the maximum price.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

int n, k;
long long base = 0, mx = 0, cnt, sum;
vector<long long> a[100000];
int f[100000];

void solve(int x, long long budget){
	if(cnt == k) return;
	if(x != -1 && budget < a[x][0]){
		x = upper_bound(f, f + x, budget) - f - 1;
	}
	if(x == -1){
		cnt++;
		sum += budget + 1;
		return;
	}
	
	solve(x - 1, budget);
	
	for(int i = 0; i < a[x].size() && a[x][i] <= budget && cnt < k; i++){
		solve(x - 1, budget - a[x][i]);
	}
}

int main(){
	freopen("roboherd.in", "r", stdin);
	freopen("roboherd.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		int m;
		cin >> m;
		
		int v[m];
		
		for(int j = 0; j < m; j++){
			cin >> v[j];
		}
		
		sort(v, v + m);
		
		base += v[0];
		mx += v[m - 1];
		
		if(m == 1){
			i--, n--;
			continue;
		} 
		
		for(int j = 1; j < m; j++){
			a[i].push_back(v[j] - v[0]);
		}
	}
	
	sort(a, a + n);
	
	for(int i = 0; i < n; i++) f[i] = a[i][0];
	
	long long l = 0, r = mx;
	
	
	while(l < r){
		long long mid = l + (r - l) / 2;
		cnt = 0;
		solve(n - 1, mid);
		
		if(cnt == k) r = mid;
		else l = mid + 1;
	}
	
	cnt = 0;
	sum = 0;
	if(l > 0) solve(n - 1, l - 1);
	
	cout << k * (base + l) - sum << endl;

	return 0;
}
