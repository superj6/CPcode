#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	freopen("cowdate.in", "r", stdin);
	freopen("cowdate.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	n++;
	long double ret = 0;
	long double p[n], f[n];
	p[0] = 0, f[0] = 1;
	
	int l = 0;
	for(int i = 1; i < n; i++){
		cin >> p[i];
		
		p[i] /= 1e6;
		f[i] = 1 - p[i];
		
		p[i] = p[i - 1] * f[i] + p[i] * f[i - 1];
		f[i] *= f[i - 1];
		
		while((p[i] - p[l] * f[i] / f[l]) / f[l] <= (p[i] - p[l + 1] * f[i] / f[l + 1]) / f[l + 1]){
			l++;
		}
		ret = max(ret, (p[i] - p[l] * f[i] / f[l]) / f[l]);
	}
	
	cout << (int)(ret * 1e6) << endl;

	return 0;
}