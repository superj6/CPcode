#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>

const double PI = 3.1415926535;
const int maxn = 200000;

pi operator+(pi a, pi b){
	return {a.first + b.first, a.second + b.second};
}

long long dist(pi a){
	return a.first * a.first + a.second * a.second;
}

pi operator*(long long a, pi b){
	return {a * b.first , a * b.second};
}

double ang(pi a){
	return fmod(atan2(a.second, a.first) + 2 * PI, 2 * PI);
}

int ang2(double a){
	return fmod(a + 2 * PI, 2 * PI) * maxn / (2 * PI);
}

int n;
pi a[maxn];
pi cur;
long long ret;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		pi p;
		cin >> p.first >> p.second;
		if(!dist(p)) continue;
		int x = ang2(ang(p) - PI / 2), y = ang2(ang(p) + PI / 2);
		a[x] = a[x] + p;
		a[y] = a[y] + -1 * p;
		if(y < x) cur = cur + p; 
	}
	
	for(int i = 0; i < maxn; i++){
		cur = cur + a[i];
		ret = max(ret, dist(cur));
	}
	
	cout << ret << endl;

	return 0;
}
