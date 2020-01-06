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