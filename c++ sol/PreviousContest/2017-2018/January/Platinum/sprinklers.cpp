/*
	For this problem, the first thing to notice is that the only points that matter are the ones that make up a max upper
bound and a min lower bound. To find these, hold an array of indices that are the x position and set the y position with the
inputs, then for the max sweep from right to left keeping the maximum value encountered so far, and for the minimum sweep from
left to right keeping the min value u encountered so far or the max value if it is lower. Now, if you were not considering the
vertical bounds and only the horizontal, you could calculate the number of rectangles by sweeping left to right and count the 
number of pairs of two points you can pick for the horizontal bounds of the rectangle located within the bounds of the calculated
min and max multiplied by how many position left you could place to the left bound of the rectangle. However, now you need to
figure out how to subtract the overcounting of the rectangles made with points located outside the left bounds by the sprinklers.
To do this, it is actually easier to switch your perspective of thinking of the y max and min to the x max and min. Because the
x min value is decreasing as the y coordinate increases, you can subtract the cases by considering the number of points less than
the min and the current x position you are considering multiplied by the number of number of heights you can have above that point
within the y max bounds. To do this, you can do the same thing you did earlier to calculate the y max and min to calculate the x
max and min, then calculate a prefix sum of the x mins as these are the number of places you can place the lower left point of the
rectangle that will be overcounting, and similarly compute a prefix sum where you also multiply each x min for a y value by its
distance to the upper bound of the rectangle. You can then easily compute as your iterating through x positions the sum of x mins
multiplied their distance to the upper bound of the rectangle. The complexity of this is O(n).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long mod = 1000000007;
const int maxn = 100000;
int n;
long long minv[maxn];
long long maxv[maxn];
long long temp[maxn];
long long sum[maxn];
long long ssum[maxn];

int main(){
	freopen("sprinklers.in", "r", stdin);
	freopen("sprinklers.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) minv[i] = sum[i] = n - 1;
	for(int i = 0; i < n; i++){
		long long x, y;
		cin >> x >> y;
		minv[x] = min(minv[x], y);
		maxv[x] = max(maxv[x], y);
		sum[y] = min(sum[y], x);
		temp[y] = max(temp[y], x);
	}
	
	for(int i = n - 2; i >= 0; i--) maxv[i] = max(maxv[i], maxv[i + 1]);
	minv[0] = min(minv[0], maxv[0]);
	for(int i = 1; i < n; i++) minv[i] = min(minv[i], min(minv[i - 1], maxv[i]));
	
	for(int i = n - 2; i >= 0; i--) temp[i] = max(temp[i], temp[i + 1]);
	sum[0] = min(sum[0], temp[0]);
	for(int i = 1; i < n; i++) sum[i] = min(sum[i], min(sum[i - 1], temp[i]));

	ssum[0] = sum[0];
	for(int i = n - 2; i >= 0; i--){
		ssum[i] = (sum[i] * (n - i)) % mod;
		sum[i] += sum[i + 1];
		ssum[i] += ssum[i + 1];

		sum[i] %= mod;
		ssum[i] %= mod;
	}
	
	long long ret = 0;
	for(int i = 0; i < n; i++){
		ret = (ret + ((((maxv[i] + 1) * (maxv[i]) / 2) % mod) * i) % mod) % mod;
		ret = (mod + ret - ((((2 * maxv[i] - minv[i] + 1) * (minv[i]) / 2) % mod) * i) % mod) % mod;
		ret = (mod + ret - (mod + ssum[minv[i]] - ssum[maxv[i]]) % mod) % mod;
		ret = (mod + ret + (((mod + sum[minv[i]] - sum[maxv[i]]) % mod) * (n - maxv[i])) % mod) % mod;
	}
	
	cout << ret << endl;

	return 0;
}
