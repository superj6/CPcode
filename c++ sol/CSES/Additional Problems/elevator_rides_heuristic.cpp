#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define ll long long
 
const int maxn = 20;
int n, m;
int b[maxn], r[maxn];
ll s[maxn];
 
bool works(int x, int it, int jt){
	if(it < 0) return 1;
	
	ll sum = 0;
	for(int i = 0; i < n; i++){
		if(b[i] >= r[0]) sum += b[i];
	}
	if(sum < s[it]) return 0;
	
	int st = (it < n - 1 && r[it] == r[it + 1] ? jt : 0);
	
	for(int i = st; i < x; i++){
		if(b[i] == r[it]){
			b[i] -= r[it];
			bool t = works(x, it - 1, st);
			b[i] += r[it];
			return t;
		}
	}
	
	for(int i = st; i < x; i++){
		if((!(i - st) || find(b + st, b + i, b[i]) - b == i) && b[i] > r[it]){
			b[i] -= r[it];
			bool t = works(x, it - 1, i);
			b[i] += r[it];
			if(t) return t;
		}
	}
	
	return 0;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cin >> r[i];
		b[i] = m;
	}
	
	sort(r, r + n);
	
	for(int i = 0; i < n; i++){
		s[i] = r[i];
		if(i) s[i] += s[i - 1];
	}
	
	int l = (s[n - 1] - 1) / m, r = n;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(works(mid, n - 1, 0)) r = mid;
		else l = mid;
	}
	
	cout << ret << endl;
 
	return 0;
}