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

const int mxn = 200;
int n;
int a[mxn], b[mxn];
vector<int> v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i] >> b[i];
	
	int ret = 1;
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < n; i++)
		for(int j = 0; j <= i; j++){
			int lx = a[j], rx = a[i];
			int ly = b[j], ry = b[i];
			if(lx > rx) swap(lx, rx);
			if(ly > ry) swap(ly, ry);
			
			v.clear();
			for(int l = 0; l < n; l++){
				if(lx <= a[l] && a[l] <= rx){
					v.push_back(b[l]);
				}
			}
			
			sort(v.begin(), v.end());
			
			int p = -1;
			for(int l : v){
				if(l <= ly && l >= ry - (rx - lx)) ret++;
				if(ry <= l && l <= ly + (rx - lx)){
					int it = lower_bound(v.begin(), v.end(), l - (rx - lx)) - v.begin();
					if(t && v[it] == l - (rx - lx)) ret--;
					int jt = lower_bound(v.begin(), v.end(), l - (rx - lx) - 1) - v.begin();
					if(~p && p != it && jt == it) ret++;
					p = it;
					it = upper_bound(v.begin(), v.end(), v[it] + (rx - lx)) - v.begin() - 1;
					ret += v[it] != l;
				}
			}
		}
		for(int i = 0; i < n; i++) swap(a[i], b[i]);
	}
	
	cout << ret << endl;

	return 0;
}