/*
	The first and easiest thing to realize for this problem is that you do not need any interval contained within another
interval. You can easily find such intervals by sorting by first point and comparing endpoints. Now, it is quite obvious you
want to do an O(nk) dp holding states of current interval going from left to right and the amount of intervals used. However,
the challenge is to find the transitions. If you think about the current segment u r on, there are only 3 possible transitions:
you could just not use the same interval meaning you set the dp as the same as the one before, you use a the dp which is
intersecting it, which should obviously be the one furthest back intersecting it as far back as possible so you can then add
to that dp the new length covered by the interval you are on, or third you transition from the closest interval which is disjoint
so you can add the full length of the interval while also getting the best dp possible as it is monotonically increasing. To find
the closest interval disjoint/fartherst interval intersecting, you can use two pointers as the intervals are sorted and no intervals
are contained within another so the right points are also montonically increasing. The complexity of this is O(nlogn) from sorting.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	freopen("lifeguards.in", "r", stdin);
	freopen("lifeguards.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	pair<int, int> a[n];
	for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
	
	sort(a, a + n);
	
	vector<pair<int, int>> t;
	for(int i = 0, r = -1; i < n; i++){
		if(r <= a[i].second){
			t.push_back(a[i]);
			r = a[i].second;
		}else if(k > 0){
			k--;
		}
	}
	
	n = t.size();
	int ans = 0;
	int dp[n][k + 1], maxv[n][k + 1];
	memset(dp, 0, sizeof(dp));
	memset(maxv, 0, sizeof(dp));
	
	for(int i = 0, j = 0; i < n; i++){
		while(t[j].second <= t[i].first) j++;
		
		int len = t[i].second - t[i].first;
		
		if(i <= k) dp[i][i] = len;
		
		for(int l = 0; l <= min(k, i); l++){
			if(i != j && l - (i - j - 1) >= 0){
				dp[i][l] = max(dp[i][l], dp[j][l - (i - j - 1)] + len - (t[j].second - t[i].first));
			}
			
			if(j > 0 && l - (i - j) >= 0){
				dp[i][l] = max(dp[i][l], maxv[j - 1][l - (i - j)] + len);
			}
			
			maxv[i][l] = dp[i][l];
			if(i > 0) maxv[i][l] = max(maxv[i][l], maxv[i - 1][l]);
		}
		
		if(n - i - 1 <= k) ans = max(ans, maxv[i][k - (n - i - 1)]);
	}
	
	cout << ans << endl;

	return 0;
}
