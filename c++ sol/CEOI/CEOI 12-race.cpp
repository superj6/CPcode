/*
	First to calculate the answer for type 0, I flatten the circle and do 2d dp representing the current range used on the circle and also
which side is the endpoint. Realize when extending the path backwards, you can never go within that range again. This means you can try all
reverse edges from the current endpoint and see if they are outside the range, and if so update the dp value for the new range using that point
and the point on the other side on the current range. All paths will eventually then end with some range on the circle, so just take the
best dp value and use the endpoint corresponding to that dp value as the starting vertex to output.
	Now To calculate the answer for type 1, realize every path that crosses the first edge once will go along the circle in only one
direction prior to clockwise before crossing, cross the edge, then be bounded by where it landed and the sides of the first edge. This means
we can calculate a second dp value for going one direction along the flattened circle and try all ranges that use that path and extend the
reverse first and forward next edge as a possible value, and try both different bounded sides created by the forward edge. To get the best
value after using the forward edge, we modify the dp mentioned for type 0 to be any range that ends at the marked endpoint but can only take up
any range within state, not necessarily touching the adjacent border. This is done by just maxing the current dp value with the one with a
range that takes up one less vertex. Now when you iterate over all forward and reverse edges of one-directional dp range you can answer get the
answer in O(1).
	However, iterating over all pairs of forward and reverse edges is too slow as along with iterating over all ranges is O(n^4), so you 
need to somehow cut off a factor of n. You can then realize that you can greedily precompute the best place to put the reverse first edge
before you iterate over the next forward edge, as depending on which side you want to go to after the next edge, you will always want the
reverse first edge to make as large a range possible on that side. This makes the complexity O(n^3), which is good enough to AC. However when
iterating over edges on the flattened circle, make sure to always stay in bounds such that the range length is less than n.
*/

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
 
const int mxn = 1000;
int n, m;
int dp[mxn][mxn][2], dp2[mxn][mxn][2];
vector<int> g[mxn], gr[mxn];
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0, x; i < n; i++)
	for(cin >> x; x; cin >> x)
	for(int j = 0; j < 2; j++)
	for(int l = 0; l < 2; l++){
		int u = j * n + i, v = l * n + x - 1;
		if(abs(u - v) < n){
			g[u].push_back(v);
			gr[v].push_back(u);
		} 
	}
	
	for(int i[2] = {0}; i[1] < 2 * n; i[1]++)
	for(i[0] = i[1]; ~i[0] && i[1] - i[0] < n; i[0]--)
	for(int j = 0; j < 2; j++){
		int &dpc = dp[i[0]][i[1]][j], dpc2 = dp2[i[0]][i[1]][j];
		if(i[0] != i[1]) dpc = max(dpc, dp[i[0] + j][i[1] - !j][j]);
		
		for(int k : gr[i[j]]) if(k != i[!j])
		for(int l = 0, ii[2]; l < 2; l++) if((k > i[l]) == l && abs(k - i[!l]) < n){
			ii[l] = k, ii[!l] = i[!l];
			int &dpx = dp[ii[0]][ii[1]][l], &dpx2 = dp2[ii[0]][ii[1]][l];
			dpx = max(dpx, dpc + 1);
			if(j == l && (i[0] == i[1] || dpc2)) dpx2 = max(dpx2, dpc2 + 1);
		}
	}
	
	int ret = 0, x = 0;
	for(int i[2] = {0}; i[1] < 2 * n; i[1]++)
	for(i[0] = i[1]; ~i[0] && i[1] - i[0] < n; i[0]--)
	for(int j = 0; j < 2; j++){
		int dpc = dp[i[0]][i[1]][j], dpc2 = dp2[i[0]][i[1]][j];
		if(dpc > ret) ret = dpc, x = i[j];
		
		if(m && (i[0] == i[1] || dpc2)){
			for(int p = 0, ii[2]; p < 2; p++){
				int d = 1 - 2 * (j ^ p), k = -1; 
				for(int l : gr[i[j]]){
					if(l != i[p] && (l > i[p]) == p && abs(l - i[!p]) < n && 
					(!~k || d * abs(l - i[!p]) > d * abs(k - i[!p]))){
						k = l;
					}
				} 
				
				if(~k) for(int l : g[i[!j]]){
					if(l != i[p] && (l > i[p]) == p && 
					abs(l - i[!p]) < n && l != k && (l < k) == j){
						ii[p] = l, ii[!p] = ~d ? i[j] : k;
						int c = dp[ii[0] + p][ii[1] - !p][p] + dpc2 + 2;
						if(c > ret) ret = c, x = k;
					}
				}
			}
		}
	}
	
	cout << ret << endl;
	cout << (x % n + 1) << endl;
	
	return 0;
}