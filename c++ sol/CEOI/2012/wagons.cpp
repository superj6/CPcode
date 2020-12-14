#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define pb push_back
 
typedef array<int, 3> T;
 
const int maxm = 1001;
int n, m, k;
int a[maxm][maxm];
vector<int> v[maxm];
vector<T> q, q2;
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> m;
	
	for(int i = 1; i <= m; i++){
		int x;
		for(cin >> x; x; cin >> x){
			a[i][x] = 1;
			v[x].pb(i);
		} 
	}
	
	int ret = 0;
	for(q.pb({0, 0, 0}); ret < n && !q.empty(); ret++){
		int x;
		cin >> x;
		
		swap(q, q2);
		q.clear();
		for(T c : q2){
			if(!c[0] && !c[2]){
				for(int i : v[x]){
					q.pb({i, 0, 0});
					q.pb({0, 0, i});
				}
			}else if(!c[2]){
				if(a[c[0]][x]){
					q.pb(c);
				}else{
					for(int i : v[x]){
						c[2] = i;
						q.pb(c);
					} 
				}
			}else if(!c[0]){
				if(a[c[2]][x]){
					q.pb(c);
				}else{
					for(int i : v[x]){
						c[0] = i;
						q.pb(c);
					} 
				}
			}else if(!c[1]){
				if(a[c[0]][x] || a[c[2]][x]){
					q.pb(c);
				}else{
					for(int i : v[x]){
						c[1] = i;
						q.pb(c);
					}
				}
			}else if(c[0] > 0){
				if(a[c[0]][x] || a[c[1]][x]){
					q.pb(c);	
				}else if(a[c[2]][x]){
					c[0] *= -1;
					q.pb(c);
				}
			}else{
				if(a[c[1]][x] || a[c[2]][x]){
					q.pb(c);
				}
			}
		}
	}
	if(q.empty()){
		ret--;
		swap(q, q2);
	}
	
	T ans = q[0];
	for(T c : q){
		if(!c[1] && !c[2]){
			ans = c;
			break;
		}
		if(!c[1] || !c[2]) ans = c;
	}
	if(!ans[1]) swap(ans[1], ans[2]);
	ans[0] = abs(ans[0]);
	
	cout << ret << endl;
	cout << ans[0] << " " << ans[1] << " " << ans[2] << endl;
 
	return 0;
}