#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxy = 1 << 20;

struct BIT{
	int bit[maxy + 2];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int ind, int val){
		ind++;
		
		for(; ind <= maxy + 1; ind += ind & (-ind)) bit[ind] += val;
	}
	
	int qry(int ind){
		ind++;
		int ret = 0;
		
		for(; ind > 0; ind -= ind & (-ind)) ret += bit[ind];
		
		return ret;
	}
};

BIT a, b;

int getsplit(){
	int l = 0, r = maxy;
	
	while(r - l > 1){
		int mid = (l + r) / 2;
		
		int a1 = a.qry(mid), b1 = b.qry(mid);
		int a2 = a.qry(maxy) - a1, b2 = b.qry(maxy) - b1;
		
		if(max(a1, b1) <= max(a2, b2)) l = mid;
		else r = mid;
	}
	
	int a1 = a.qry(l), b1 = b.qry(l);
	int a2 = a.qry(maxy) - a1, b2 = b.qry(maxy) - b1;
	
	return max(max(a1, b1), max(a2, b2));
}

int main(){
	freopen("balancing.in", "r", stdin);
	freopen("balancing.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	pair<int, int> points[n];
	
	for(int i = 0; i < n; i++){
		cin >> points[i].first >> points[i].second;
		a.add(points[i].second, 1);
	}
	
	sort(points, points + n);
	
	int best = getsplit();
	
	for(int i = 0; i < n; i++){
		a.add(points[i].second, -1), b.add(points[i].second, 1);
		
		if(i == n - 1 || points[i].first != points[i + 1].first) best = min(best, getsplit());
	}
	
	cout << best << endl;

	return 0;
}