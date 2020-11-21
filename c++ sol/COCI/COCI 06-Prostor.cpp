/*
  First figure out how to count intersections of rectangles in one 2d plane and it is easy to extend. Instead of counting of number
of intersecting directly, it is easier to count the inverse. You do this by for each 90 degree rotation of a rectangle, query a bit
for the the number of points in it less than the closest side in that direction then add the farthest point in that direction from
the rectangle. This counts all pairs such that one is completely to one side of another rectangle. However, this will overcount a 
rectangle that is completely to two sides of a rectangle, so also add and query similarly along closest and furthest corner of a 
rectangle using a 2d bit. Then just subtract this from the total pairs to get the number of intersecting pairs. To extend to 3d, just
try each plane in each direction and hold rectangles not along the current axis direction as line rectangles that will be put in the 
bits for multiple coordinates at a time, and like prefix sums iterate through coordinates and add or subtract rectangle at the points
that its in. Make sure to only count pairs between different coordinates only once. It is O(n * lg^2(k)).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<pi, pi>
#define piii pair<int, pii>
#define f first
#define s second

const int k = 1001;
struct BIT{
	int bit[k];
	
	BIT(){ memset(bit, 0, sizeof(k));}
	
	void add(int x, int v){
		for(; x < k; x += x & -x) bit[x] += v;
	}
	
	int qry(int x){
		int ret = 0;
		for(; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

const int mxn = 100000, m = 3;
int n;
int a[mxn][m], b[mxn][m];
BIT bit, bit2[mxn];
vector<piii> v[k];

void add(int x, int y, int v){
	for(; x < k; x += x & -x) bit2[x].add(y, v);
}

int qry(int x, int y){
	int ret = 0;
	for(; x; x -= x & -x) ret += bit2[x].qry(y);
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++) cin >> a[i][j];
		for(int j = 0; j < m; j++){
			cin >> b[i][j];
			if(a[i][j] > b[i][j]) swap(a[i][j], b[i][j]);
		} 
	}
	
	ll ret = 0;
	for(int t = 0; t < m; t++){
		for(int i = 1; i < k; i++) v[i].clear();
		for(int i = 0; i < n; i++){
			for(int j = 0; j <= t; j++) if(a[i][j] == b[i][j]){
				pii p = {{a[i][1], a[i][2]}, {b[i][1], b[i][2]}};
				v[a[i][0]].push_back({1 + j, p});
				v[b[i][0] + 1].push_back({-1 - j, p});
			}
			rotate(a[i], a[i] + m - 1, a[i] + m);
			rotate(b[i], b[i] + m - 1, b[i] + m);
		}
		for(int i = 1, f = 0; i < k; i++){
			sort(v[i].begin(), v[i].end(), [](piii x, piii y){
				return (x.f < 0) != (y.f < 0) ? x.f < y.f : x.f > y.f;
			});
			for(piii j : v[i]){
				int x = j.f;
				ret += !~-x * f, f += x / abs(x);
			}
		}
		for(int s = 0; s < 4; s++)
		for(int i = 1; i < k; i++)
		for(piii &j : v[i]){
			int x = j.f;
			pii &p = j.s;
			if(!~-x) ret += qry(p.f.f - 1, p.f.s - 1) - bit.qry(p.f.f - 1);
			add(p.s.f, p.s.s, x / abs(x)), bit.add(p.s.f, x / abs(x));
			swap(p.f.f, p.f.s), swap(p.s.f, p.s.s), swap(p.f.f, p.s.f);
			p.f.f = k - p.f.f, p.s.f = k - p.s.f;
		}
	}
	
	cout << ret << endl;

	return 0;
}
