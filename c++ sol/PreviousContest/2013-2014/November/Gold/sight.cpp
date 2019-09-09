#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
#define endl '\n'

double pi = 3.14159265358979323846;

int main(){
	freopen("sight.in", "r", stdin);
	freopen("sight.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	long long r;
	cin >> n >> r;
	
	pair<double, double> circle[n];
	
	for(int i = 0; i < n; i++){
		long long x, y;
		cin >> x >> y;
		double angle = atan2(y, x), diff = acos(r / sqrt(1.0 * x * x + 1.0 * y * y));
		
		circle[i].first = angle - diff;
		if(circle[i].first < 0) circle[i].first += 2 * pi; 
		circle[i].second = circle[i].first + 2 * diff;
	}
	
	sort(circle, circle + n);
	
	int total = 0;
	priority_queue<double, vector<double>, greater<double>> pq;
	
	for(int it = 0; it < 2; it++){
		for(int i = 0; i < n; i++){
			while(!pq.empty() && pq.top() < circle[i].first) pq.pop();
			
			if(it == 1) total += pq.size();
			
			pq.push(circle[i].second);
			circle[i].first += 2 * pi;
			circle[i].second += 2 * pi;
		}
	}
	
	cout << total << endl;

	return 0;
}