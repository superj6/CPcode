/*
	The naive solution to this is to try all triangles and then test every point to see if it is inside. This right away is
O(n^4), however, this is not fast enough for n = 300. However, because the n bounds is relatively small, you can see that an O(n^3)
solution would work. This means you could still iterate over all triangles in time, however, you would then have to calculate the
number of points in a triangle in O(1). To do this, first think about how you can split counting up the triangle into counting
something for each line. You can see that that every triangle can be confined bythe area of 1 or 2 segments on top minus the area
of other 2 or 1 segments on the bottom. This means what you can do is precalculate the number of under each segment in O(n^3) by
iterating over every segment and testing if every point is under it, then iterate over every triangle and set the number of points
for that triangle equal to the number of points under the top segments minus the number of points under the bottom segments of the
triangle. You then just have to be careful about the case when points are on a line. The solutions therefore is O(n^3) as desired.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <complex>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'

typedef long long num;
typedef complex<num> point;

num cp(point a, point b, point c){
	return imag(conj(a - b) * (c - b));
}

bool cpl(point a, point b, point c){
	return cp(a, b, c) < 0;
}

bool under(point a, point b, point c){
	return cpl(a, b, c) && real(c - a) > 0 && real(b - c) > 0;
}

int main(){
	freopen("triangles.in", "r", stdin);
	freopen("triangles.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	vector<point> points;
	
	for(int i = 0; i < n; i++){
		num x, y;
		cin >> x >> y;
		points.push_back(point(x, y));
	}
	
	sort(points.begin(), points.end(), [&](point a, point b)->bool{
		return real(b - a) > 0;
	});
	
	int cnt[n][n];
	memset(cnt, 0, sizeof(cnt));
	
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			for(int k = 0; k < n; k++){
				if(under(points[i], points[j], points[k])) cnt[i][j]++;
			}
		}
	}
	
	num amt[n - 2];
	memset(amt, 0, sizeof(amt));
	
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			for(int k = j + 1; k < n; k++){
				if(under(points[i], points[k], points[j])){
					amt[cnt[i][k] - cnt[i][j] - cnt[j][k] - 1]++;
				}else{
					amt[cnt[i][j] + cnt[j][k] - cnt[i][k]]++;
				}
			}
		}
	} 
	
	for(int i = 0; i < n - 2; i++) cout << amt[i] << endl;

}
