/*
	This is an interesting problem as the technique used in the solution is not obvious that it would be used at all.
To start, a good idea with any problem with indexed values is to graph the values with index on the x-axis and values on the
y-axis. Intuitively, one can see that the optimal points in the plotted graph are the ones that form the upper convex hull
adding on both sides points with y values 0. You can then find for every point the two values on the convex hull on either
side of the current value, and output the weighted average based on the distance to each. This can be done with two pointers
or a binary search. The complexity of this is O(nlogn) due to the creation of the convex hull.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <complex>
#include <vector>
using namespace std;
#define endl '\n'

typedef long long num;
typedef complex<num> point;
typedef vector<point> poly;

num cp(point a, point b, point c){
	return imag(conj(a - c) * (b - c));
}

bool ccweq(point a, point b, point c){
	return cp(a, b, c) <= 0;
}

void unwind(poly& p, point a){
	int sz = p.size();
	while(sz > 1 && ccweq(a, p[sz - 1], p[sz - 2])) sz--;
	p.resize(sz);
}

poly hull(poly p){
	point pivot = p[0];
	
	poly ret(1, pivot);
	
	for(int i = 1; i < p.size(); i++){
		unwind(ret, p[i]);
		ret.push_back(p[i]);
	}
	
	if(ret.size() > 2){
		unwind(ret, pivot);
	}
	
	return ret;
}

poly p;

num answer(int x){
	int l = 0, r = p.size() - 1;
	
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(real(p[mid]) <= x) l = mid;
		else r = mid;
	}
	
	return 100000 * ((x - real(p[l])) * imag(p[l + 1])  + (real(p[l + 1]) - x) * imag(p[l])) / real(p[l + 1] - p[l]);
}

int main(){
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	p.push_back(point(0, 0));
	
	for(int i = 0; i < n; i++){
		int x = i + 1, y;
		cin >> y;
		
		p.push_back(point(x, y));
	}
	
	p.push_back(point(n + 1, 0));
	
	p = hull(p);
	
	for(int i = 1; i <= n; i++){
		cout << answer(i) << endl;
	}

	return 0;
}
