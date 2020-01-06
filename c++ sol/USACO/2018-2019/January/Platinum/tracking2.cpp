/*
	The first step to this problem is to think about the simpler case where there is only one value as the minimum for the
whole range. To solve this, set dp[i] as the number of ways to have i values in a row with the same minimum value such that the
ith value is equal to the minimum. Let v be the minimum value and x be 10^9 - v, or in other words, the number of values possible
strictly greater than the minimum. An O(nk) solution to this case is dp[i] = dp[i - 1] + x * dp[i - 2] + ... + x^(k - 1) * dp[i - k].
This is because you are considering every case where the vallue of i - j = v and every value between i - j and i is some number
greater than v. However, if you subtract x * dp[i] from dp[i + 1] and similarly subtracting their expanded equalities gives a
recurrence of dp[i + 1] = (x + 1) * dp[i] - x^k * dp[i - k], an O(n) solution. Also, the solution for this dp when solving for
l values in a row is dp[l + 1] because you do not need the lth value to be equal to v, as the definition of the dp state is. Now
to solve for the general case, you just have to just carefully consider transitions and then run the dp described above whenever
you encounter a list of multiple values in a row. It is easier to convert the list of values into a list of pairs containg a
value and how many times in a row it appears. Let the array of pairs be a, with a[i].first be the value of the ith pair and
a[i].second be the amount of times in a row it appears. If there is only one pair, output the solution to that and you are done.
Otherwise iterate through the pairs and look at the transitions in the code below, being careful to consider the case when you
are dealing with the first and last pair. The overall complexity is O(n).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const long long mod = 1000000007;
int n, k;
vector<pair<int, int>> a;

long long solve(int x, int l){
	x = mod - x - 7;
	long long p = 1;
	long long dp[l + 2];
	dp[0] = dp[1] = 1;
	for(int i = 1; i <= k; i++){
		p = (p * x) % mod;
	}
	for(int i = 1; i <= l; i++){
		dp[i + 1] = (dp[i] * (x + 1)) % mod;
		if(i >= k) dp[i + 1] = (dp[i + 1] - (dp[i - k] * p) % mod + mod) % mod;
	}
	return dp[l + 1];
}

int main(){
	freopen("tracking2.in", "r", stdin);
	freopen("tracking2.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i <= n - k; i++){
		int x;
		cin >> x;
		if(a.size() > 0 && x == a.back().first) a.back().second++;
		else a.push_back({x, 1});
	}
	
	if(a.size() == 1){
		cout << solve(a[0].first, n) << endl;
		return 0;
	}
	
	long long ret = 1;
	for(int i = 0; i < a.size(); i++){
		int l;
		if(i == 0){
			if(a[i].first < a[i + 1].first){
				l = a[i].second - 1;
			}else{
				l = a[i].second + k - 1;
			}
		}else if(i == a.size() - 1){
			if(a[i].first < a[i - 1].first){
				l = a[i].second - 1;
			}else{
				l = a[i].second + k - 1;
			}
		}else{
			if(a[i].first < a[i - 1].first){
				if(a[i].first < a[i + 1].first){
					l = max(0, a[i].second - k - 1);
				}else{
					l = a[i].second - 1;
				}
			}else{
				if(a[i].first < a[i + 1].first){
					l = a[i].second - 1;
				}else{
					l = a[i].second + k - 1;
				}
			}
		}
		ret = (ret * solve(a[i].first, l)) % mod;
	}
	
	cout << ret << endl;

	return 0;
}
