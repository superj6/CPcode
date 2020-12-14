/*
  NAME: super_j6
  LANG: C++
  PROG: dcircle
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n;
string s;
vector<int> v, w;
int mn[2], mx[2];
void answer(){
	cin >> s;
	n = s.size();
	
	v.resize(n);
	for(int i = 0; i < n; i++) v[i] = s[i] == 'M';
	
	while(v.size() > 1){
		n = v.size();
		
		w.clear();
		while(~-v.size() && v.back() == v[0]){
			w.push_back(v.back());
			v.pop_back();
		}
		reverse(w.begin(), w.end());
		v.insert(v.begin(), w.begin(), w.end());
		
		mn[0] = mn[1] = n, mx[0] = mx[1] = 0;
		for(int i = 0, j = 1; i < n; i++, j++){
			if(i == n - 1 || v[i] != v[i + 1]){
				mn[v[i]] = min(mn[v[i]], j);
				mx[v[i]] = max(mx[v[i]], j);
				j = 0;
			}
		}
		
		if(mx[0] < mx[1]){
			swap(mn[0], mn[1]), swap(mx[0], mx[1]);
			for(int i = 0; i < n; i++) v[i] ^= 1;
		}
		
		if(v[0]) reverse(v.begin(), v.end());
		
		if(mn[0] + 1 < mx[0] || mx[1] > 1){
			cout << 0 << endl;
			return;
		}
		
		swap(v, w), v.clear();
		for(int i = mn[0]; i < n; i += !w[i] + mx[0]){
			v.push_back(w[i]);
		}
	}
	
	cout << 1 << endl;
}

int main(){
	freopen("dcircle.in", "r", stdin);
	freopen("dcircle.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}