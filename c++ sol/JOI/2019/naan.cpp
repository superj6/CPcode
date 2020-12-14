#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

struct fr{
	__int128 x, y;
	
	fr(__int128 X = 0, __int128 Y = 1){
		x = X, y = Y;
		ll g = __gcd(x, y);
		x /= g, y /= g;
	}
	
	friend fr operator+(fr a, fr b){
		return fr(a.x * b.y + b.x * a.y, a.y * b.y);
	}
	
	friend fr operator-(fr a, fr b){
		return fr(a.x * b.y - b.x * a.y, a.y * b.y);
	}
	
	friend fr operator*(fr a, fr b){
		return fr(a.x * b.x, a.y * b.y);
	}
	
	friend fr operator/(fr a, fr b){
		return fr(a.x * b.y, a.y * b.x);
	}
	
	friend bool operator<(fr a, fr b){
		return a.x * b.y < b.x * a.y;
	}
};

const int mxn = 2001;
int n, m;
fr a[mxn][mxn];
bool vis[mxn];
int vi[mxn];
fr vf[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++){
		ll x;
		cin >> x;
		a[i][j] = fr(x) + a[i][j - 1];
	}
	
	for(int i = 1; i <= n; i++){
		vf[i] = fr(m + 1);
		for(int j = 1; j <= n; j++){
			if(vis[j]) continue;
			fr x = a[j][m] * fr(i, n);
			int it = lower_bound(a[j], a[j] + m, x) - a[j] - 1;
			fr y = fr(it) + (x - a[j][it]) / (a[j][it + 1] - a[j][it]);
			if(y < vf[i]) vi[i] = j, vf[i] = y;
		}
		vis[vi[i]] = 1;
		if(i < n) cout << (ll)vf[i].x << " " << (ll)vf[i].y << endl;
	}
	
	cout << vi[1];
	for(int i = 2; i <= n; i++) cout << " " << vi[i];
	cout << endl;

	return 0;
}