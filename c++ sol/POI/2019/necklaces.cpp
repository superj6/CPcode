#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>
#include <complex>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

//poly ops
typedef vector<int> poly;

poly operator+(poly a, poly b){
  int n = max(a.size(), b.size());
  a.resize(n), b.resize(n);

  poly ans(a);
  for(int i = 0; i < n; i++) ans[i] += b[i];
  while(!ans.empty() && !ans.back()) ans.pop_back();
  
  return ans;
}

//fft
typedef double ld;
typedef complex<ld> cd;
typedef vector<cd> vcd;
const ld PI = acos(-1);

void fft(vcd &a, int f){
  int n = a.size();

  for(int i = 1, j = 0; i < n; i++){
    int k = n >> 1;
    for(; j & k; k >>= 1) j ^= k;
    j ^= k;
    if(i < j) swap(a[i], a[j]);
  }

  for(int k = 2; k <= n; k <<= 1){
    ld ang = 2 * PI / k * (1 - 2 * f);
    cd wl(cos(ang), sin(ang));
    for(int i = 0; i < n; i += k){
      cd w(1);
      for(int j = 0; 2 * j < k; j++){
        cd u = a[i + j], v = w * a[i + j + k / 2];
        a[i + j] = u + v, a[i + j + k / 2] = u - v;
        w *= wl;
      }
    }
  }

  if(f) for(cd &x : a) x /= n;
}

poly operator*(poly a, poly b){
	vcd fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < a.size() + b.size() - 1) n <<= 1;
	fa.resize(n), fb.resize(n);
	
	fft(fa, 0), fft(fb, 0);
	for(int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, 1);
	
	poly ans(n);
	for(int i = 0; i < n; i++) ans[i] = roundl(fa[i].real());
	while(!ans.empty() && !ans.back()) ans.pop_back();
		
	return ans;
}
//end fft
//end poly ops


int n[2];
poly v[2][2];
poly a[2][2][2];

void pr(){
	for(int t = 0; t < 2; t++){
		for(int j = 0; j < 2; j++){
			for(int i = 0; i <= n[t]; i++){
				cout << v[t][j][2 * n[t] + i] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void answer(){
	for(int i = 0; i < 2; i++) cin >> n[i];
	
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < 2; i++){
			v[t][i].assign(0, 0);
			for(int j = 0; j < 2; j++) a[t][i][j].assign(2 * n[t] + 1, 0);
		}
		
		for(int i = 0, j = 0; i <= n[t]; i++){
			if(i){
				int x;
				cin >> x;
				j ^= (x & 1);
			}
			for(int l = 0; l < 2; l++){
				a[t][j][l][n[t] + (2 * l - 1) * i]++;
			}
		}
		
		for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++){
			v[t][i ^ j] = v[t][i ^ j] + a[t][i][0] * a[t][j][1];
		}
		for(int i = 0; i < 2; i++) v[t][i].resize(3 * n[t] + 1);
	}
	
	//pr();
	
	for(int i = min(n[0], n[1]); ~i; i--)
	for(int j = 0; j < 2; j++){
			bool p = 1;
			for(int t = 0; t < 2; t++) p &= v[t][j][2 * n[t] + i] > 0;
			if(p){
				cout << i << endl;
				return;
			}
	}
	cout << -1 << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;

	for(int i = 0; i < t; i++) answer();

	return 0;
}