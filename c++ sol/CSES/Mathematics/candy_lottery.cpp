#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

double p(double x, int e){
	double ret = 1;
	for(; e > 0; e >>= 1){
		if(e & 1) ret *= x;
		x *= x;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << setprecision(6) << fixed;
	
	int n, k;
	cin >> n >> k;
	
	double sum = 0;
	double f[k];
	
	for(int i = 0; i < k; i++){
		f[i] = p(i + 1, n) - sum;
		sum += f[i];
	}
	
	double ret = 0;
	for(int i = 0; i < k; i++){
		ret += (i + 1) * f[i] / sum;
	}
	
	cout << ret << endl;

	return 0;
}