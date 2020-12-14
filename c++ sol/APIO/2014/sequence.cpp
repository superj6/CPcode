#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define pii pair<pi, int>
#define f first
#define s second
 
const int maxn = 100000, maxk = 202;
int n, k;
int p[maxk][maxn];
pii l[maxk][maxn];
int s[maxk], e[maxk];
ll c;
int ans[maxk];
 
bool cp(pii x, pii y, pii z){
	return (x.f.f - z.f.f) * (y.f.s - x.f.s) >= (x.f.f - y.f.f) * (z.f.s - x.f.s);
}
 
ll f(ll x, ll y, ll z){
	return l[x][y].f.f * z + l[x][y].f.s;	
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	k++;
	
	l[0][0] = {{0, 0}, -1};
	for(int i = 1; i <= k; i++) l[i][0] = {{0, 0x3f3f3f3f}, -1};
	for(int i = 0; i < n; i++){
		ll x;
		cin >> x;
		c += x;
		for(int j = k; j; j--){
			while(e[j - 1] - s[j - 1] > 1 && f(j - 1, s[j - 1], c) >= f(j - 1, s[j - 1] + 1, c)) s[j - 1]++;
			p[j][i] = l[j - 1][s[j - 1]].s;
			pii x = {{-2 * c, 2 * c * c + f(j - 1, s[j - 1], c)}, i};
			while(e[j] - s[j] > 2 && cp(l[j][e[j] - 2], l[j][e[j] - 1], x)) e[j]--;
			l[j][e[j]++] = x;
		}
	}
	
	for(int i = k - 2, j = p[k][n - 1]; ~i; j = p[i-- + 1][j]) ans[i] = j + 1;
	
	cout << ((2 * c * c - l[k][e[k] - 1].f.s) / 2) << endl;
	cout << ans[0];
	for(int i = 1; i < k - 1; i++) cout << " " << ans[i];
	cout << endl;
 
	return 0;
}