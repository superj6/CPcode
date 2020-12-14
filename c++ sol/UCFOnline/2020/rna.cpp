#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define ull unsigned ll
#define pi pair<int, int>
#define f first
#define s second

const ull ha = 1000696969;
const int n = 1000001, m = 64, w = 3;
int k;
string s;
string d[m];
int a[m];
ull p[n];
vector<ull> v[w];
set<ull> f;

void answer(){
	cin >> s;
	
	for(int i = 0; i < m; i++) cin >> d[i] >> a[i];

	cin >> k;
	k /= w;
	
	for(int i = 0; i < w; i++) v[i].assign(1, 0);

	p[0] = 1;
	for(int i = 0; i <= s.size() - w; i++){
		p[i + 1] = p[i] * ha;
		v[i % w].push_back(a[find(d, d + m, s.substr(i, 3)) - d]);
	}

	f.clear();
	for(int t = 0; t < w; t++)
	for(int i = 1; i < v[t].size(); i++){
		v[t][i] += ha * v[t][i - 1];
		if(i >= k) f.insert(v[t][i] - p[k] * v[t][i - k]);
	}
	
	cout << f.size() << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}