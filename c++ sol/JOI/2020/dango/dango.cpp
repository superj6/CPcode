#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <random>
#include <chrono>
#include <vector>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int mxn = 500, k = 4, mxt = 40000000, w = 3;
const char c[w + k] = {'P', 'W', 'G', '/', '|', '\\', '-'};
typedef pair<array<pi, w>, int> T;
int n, m;
uint8_t a[mxn][mxn], b[mxn][mxn];
int vis[mxn][mxn];
vector<T> v;
int dx[2 * k] = {1, 1, 1, 0, -1, -1, -1, 0};
int dy[2 * k] = {-1, 0, 1, 1, 1, 0, -1, -1};

int main(){
  freopen("in.txt", "r", stdin);
  freopen("out6.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		char x;
		cin >> x;
		a[i][j] = find(c, c + w, x) - c;
	} 
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		if(!~-a[i][j]){
			for(int p = 0; p < 2 * k; p++){
				v.push_back(T());
				v.back().f[1] = {i, j}, v.back().s = w + p % k; 
				for(int l = 0; l < 2; l++){
					int x = i + dx[(p + l * k) % (2 * k)], y = j + dy[(p + l * k) % (2 * k)];
					if(x >= 0 && y >= 0 && x < n && y < m && a[x][y] == 2 * l){
						v.back().f[2 * l] = {x, y};
					}else{
						v.pop_back();
						break;
					}
				}
			}
		}
	}
	
	memset(vis, -1, sizeof(vis));
	for(int t = 0, tt = 0; t < mxt; t += tt){
		int it = uniform_int_distribution<int>(0, v.size() - 1)(rng);
		
		int x = -1;
		for(pi i : v[it].f){
			if(~vis[i.f][i.s]){
				if(!~x) x = vis[i.f][i.s];
				else x = -2;
			}
		}
		
		if(x != -2 && x != it){
			if(~x){
				for(pi i : v[x].f)  vis[i.f][i.s] = -1;
				a[v[x].f[1].f][v[x].f[1].s] = 1;
			}
			for(pi i : v[it].f) vis[i.f][i.s] = it;
			a[v[it].f[1].f][v[it].f[1].s] = v[it].s;
			
			if(tt && !~x){
        			t = 0;
        			memcpy(b, a, sizeof(a));
      			}
		}else if(!tt){
			tt = 1;
			memcpy(b, a, sizeof(a));
		}
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++) cout << c[b[i][j]];
		cout << endl;
	}

	return 0;
}