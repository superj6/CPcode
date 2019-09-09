#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

struct point{
	int x, y;
	
	point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

int n, q;
int qa, qb;
int delta[300000], dist[300000];
vector<point> points;


int pdist(int a, int b){
	a--, b--;
	return abs(points[a].x - points[b].x) + abs(points[a].y - points[b].y);
}

void build(int rt, int a, int b){
	if(a > b) return;
	if(a == b){
		if(a < n - 1) delta[rt] = pdist(a, a + 1) + pdist(a + 1, a + 2) - pdist(a, a + 2);
		else delta[rt] = 0;
		if(a < n) dist[rt] = pdist(a, a + 1);
		else dist[rt] = 0;
		
		return;
	}
	
	int mid = (a + b) / 2;
	build(rt * 2, a, mid);
	build(rt * 2 + 1, mid + 1, b);
	delta[rt] = max(delta[rt * 2], delta[rt * 2 + 1]);
	dist[rt] = dist[rt * 2] + dist[rt * 2 + 1];
}

int query_dist(int rt, int a, int b){
	if(a > qb || b < qa) return 0;
	if(qa <= a && b <= qb) return dist[rt];
	int mid = (a + b) / 2;
	return query_dist(rt * 2, a, mid) + query_dist(rt * 2 + 1, mid + 1, b);
}

int query_delta(int rt, int a, int b){
	if(a > qb || b < qa) return 0;
	if(qa <= a && b <= qb) return delta[rt];
	int mid = (a + b) / 2;
	return max(query_delta(rt * 2, a, mid), query_delta(rt * 2 + 1, mid + 1, b));
}

void update_dist(int rt, int a, int b){
	if(a > qb || b < qa) return;
	if(qa <= a && b <= qb){
		if(a >= 1 && a < n) dist[rt] = pdist(a, a + 1);
		else dist[rt] = 0;
		return;
	}
	
	int mid = (a + b) / 2;
	update_dist(rt * 2, a, mid);
	update_dist(rt * 2 + 1, mid + 1, b);
	dist[rt] = dist[rt * 2] + dist[rt * 2 + 1];
}

void update_delta(int rt, int a, int b){
	if(a > qb || b < qa) return;
	if(qa <= a && b <= qb){
		if(a >= 1 && a < n - 1) delta[rt] = pdist(a, a + 1) + pdist(a + 1, a + 2) - pdist(a, a + 2);
		else delta[rt] = 0;
		return;
	}
	
	int mid = (a + b) / 2;
	update_delta(rt * 2, a, mid);
	update_delta(rt * 2 + 1, mid + 1, b);
	delta[rt] = max(delta[rt * 2], delta[rt * 2 + 1]);
}


int main(){
	ifstream fin ("marathon.in");
	ofstream fout ("marathon.out");

	fin >> n >> q;
	
	for(int i = 0; i < n; i++){
		int x, y;
		fin >> x >> y;
		
		points.push_back(point(x, y));
	}
	
	
	build(1, 1, n);
	
	for(int i = 0; i < q; i++){
		char task;
		fin >> task;
		
		if(task == 'U'){
			int r, nx, ny;
			fin >> r >> nx >> ny;
			r--;
			points[r].x = nx, points[r].y = ny;
			r++;
			for(int j = r - 1; j <= r; j++){
				qa = j, qb = j;
				update_dist(1, 1, n);
			}
			for(int j = r - 2; j <= r; j++){
				qa = j, qb = j;
				update_delta(1, 1, n);
			}
			
		}else{
			fin >> qa >> qb;
			qb--;
			int tot = query_dist(1, 1, n);
			qb--;
			int del = query_delta(1, 1, n);
			fout << (tot - del) << endl;
		}
	}
	

	return 0;
}