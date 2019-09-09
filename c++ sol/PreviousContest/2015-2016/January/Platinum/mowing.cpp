#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'

struct point{
	int x1, x2, y1, y2, t;
	
	point(int x1, int x2, int y1, int y2, int t){
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = min(y1, y2);
		this->y2 = max(y1, y2);
		this->t = t;
	}
	
	friend bool operator<(point a, point b){
		return (a.x1 == b.x1 ? a.x2 < b.x2 : a.x1 < b.x1);
	}
};

struct segTree{
	int l, r;
	segTree *c[2];
	int val;
	
	segTree(int a, int b){
		l = a;
		r = b;
		val = 0;
		c[0] = c[1] = NULL;
	}
	
	segTree* get(int i){
		if(!c[i]){
			int mid = (l + r) / 2;
			if(!i){
				c[i] = new segTree(l, mid);
			}else{
				c[i] = new segTree(mid + 1, r);
			}
		}
		
		return c[i];
	}
	
	void add(int y, int v){
		val += v;
		if(l == r) return;
		
		int mid = (l + r) / 2;
		if(y <= mid) get(0)->add(y, v);
		else get(1)->add(y, v);
	}
	
	int amt(int y1, int y2){
		if(l >= y2 || r <= y1) return 0;
		if(l > y1 && r < y2) return val;
		
		return (c[0] ? c[0]->amt(y1, y2) : 0) + (c[1] ? c[1]->amt(y1, y2) : 0);
	}
};

segTree *bit[(1 << 17) + 1];

void add(int t, int y){
	
	while(t <= (1 << 17)){
		if(!bit[t]) bit[t] = new segTree(0, (1 << 30));
		bit[t]->add(y, 1);
		t += t & (-t);
	}
}

void del(int t, int y){
	
	while(t <= (1 << 17)){
		bit[t]->add(y, -1);
		t += t & (-t);
	}
}

int amt(int t, int y1, int y2){
	int ret = 0;
	
	while(t > 0){
		ret += (bit[t] ? bit[t]->amt(y1, y2) : 0);
		t -= t & (-t);
	}
	
	return ret;
}

int main(){
	freopen("mowing.in", "r", stdin);
	freopen("mowing.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, t;
	cin >> n >> t;
	
	int lx, ly;
	cin >> lx >> ly;
	
	vector<point> points;
	
	for(int i = 1; i < n; i++){
		int x, y;
		cin >> x >> y;
		
		if(lx == x){
			points.push_back(point(x, x, y, ly, i));
		}else{
			points.push_back(point(x, lx, y, y, i));
			points.push_back(point(lx, x, y, y, i));
		}
		
		lx = x;
		ly = y;
	}
	
	sort(points.begin(), points.end());
	for(int i = 1; i <= (1 << 17); i++) bit[i] = NULL;
	
	int total = 0;
	
	for(int i = 0; i < points.size(); i++){
		
		if(points[i].x1 == points[i].x2){
			if(points[i].t + t < (1 << 17)) total += amt((1 << 17), points[i].y1, points[i].y2) - amt(points[i].t + t, points[i].y1, points[i].y2);
			if(points[i].t - t > 0) total += amt(points[i].t - t, points[i].y1, points[i].y2);
		}else if(points[i].x1 < points[i].x2){
			add(points[i].t, points[i].y1);
		}else{
			del(points[i].t, points[i].y1);
		}
		
	}

	cout << total << endl;

	return 0;
}