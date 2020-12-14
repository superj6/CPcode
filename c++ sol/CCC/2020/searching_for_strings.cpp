#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define ull unsigned ll

const int ma = 1000696969, mb = 101;
const int maxn = 200000, k = 26;
int n, m;
string s, t;
ull a[maxn], p[maxn];
int cs[k], ct[k];
set<ull> vis;

ull hsh(ll c, ll d){
	return c * ma + mb + d;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t >> s;
	n = s.size(), m = t.size();
	
	for(int i = 0; i < m; i++) ct[t[i] - 'a']++;
	
	p[0] = 1;
	for(int i = 0; i < n; i++){
		a[i + 1] = hsh(a[i], s[i]);
		p[i + 1] = p[i] * ma;
		
		cs[s[i] - 'a']++;
		if(i >= m)cs[s[i - m] - 'a']--;
		if(i >= m - 1){
			bool t = 1;
			for(int j = 0; j < k; j++) t &= cs[j] == ct[j];
			if(t) vis.insert(a[i + 1] - a[i - m + 1] * p[m]);
		}
	}
	
	cout << vis.size() << endl;

	return 0;
}