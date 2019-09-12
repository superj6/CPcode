#include <iostream>
#include <cstdio>
#include <algorithm>
#include <complex>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define cd complex<double>
 
const double Pi = 3.1415926535;
 
void fft(vector<cd> &a, bool inv){
	int n = a.size();
	if(n == 1) return;
	vector<cd> a0(n / 2), a1(n / 2);
	
	for(int i = 0; 2 * i < n; i++){
		a0[i] = a[2 * i];
		a1[i] = a[2 * i + 1];
	}
	
	fft(a0, inv);
	fft(a1, inv);
	
	double ang = 2 * Pi / n * (inv ? -1 : 1);
	cd w(1), nw(cos(ang), sin(ang));
	for(int i = 0; 2 * i < n; i++){
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if(inv){
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}
		w *= nw;
	}
}
 
vector<double> mult(vector<double> &a, vector<double> &b){
	int n = 1;
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	while(n < a.size() + b.size()) n <<= 1;
	fa.resize(n), fb.resize(n);
	
	fft(fa, 0);
	fft(fb, 0);
	for(int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, 1);
	
	vector<double> ret(n);
	for(int i = 0; i < n; i++) ret[i] = round(fa[i].real());
	
	while(ret.size() > 0 && ret.back() == 0) ret.pop_back();
	
	return ret;
}
 
vector<double> dice = {0, 1, 1, 1, 1, 1, 1};
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setprecision(6) << fixed;
	
	int n, a, b;
	cin >> n >> a >> b;
	
	vector<double> ret(1, 1);
	
	for(; n > 0; n >>= 1){
		if(n & 1) ret = mult(ret, dice);
		dice = mult(dice, dice);
	}
	
	double num = 0, den = 0;
	
	for(int i = 0; i < ret.size(); i++){
		den += ret[i];
		if(a <= i && i <= b) num += ret[i];
	}
	
	cout << (num / den) << endl;
	
	return 0;
}