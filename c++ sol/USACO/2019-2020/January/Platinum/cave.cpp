#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long mod = 1000000007;
const int maxn = 1000;
int n, m;
long long par[maxn * maxn], rnk[maxn * maxn], val[maxn * maxn];
bool used[maxn * maxn], used2[maxn * maxn];
bool grid[maxn][maxn];

int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}

void unionf(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return;
	if(rnk[x] < rnk[y]) swap(x, y);
	if(rnk[x] == rnk[y]) rnk[x]++;
	par[y] = x;
	used[x] |= used[y];
	used2[x] &= used2[y];
	val[x] *= val[y];
	val[x] %= mod;
}

int main(){
	freopen("cave.in", "r", stdin);
	freopen("cave.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		char c;
		cin >> c;
		grid[i][j] = (c == '.');
		par[i * m + j] = i * m + j;
		val[i * m + j] = 1;
	}
	
	long long ret = 1;
	for(long long i = n - 2, tot = 1; i > 0; i--){
		for(int j = 1; j < m - 1; j++){
			if(grid[i][j]){
				used[find(i * m + j)] = 1;
				if(grid[i][j - 1]){
					unionf(i * m + j, i * m + j - 1);
				}
				if(grid[i + 1][j]){
					unionf(i * m + j, (i + 1) * m + j);
				}
			}
		}
		
		long long x1 = 1, x2 = 1;
		for(int j = 1; j < m - 1; j++){
			if(grid[i + 1][j] && used2[find((i + 1) * m + j)]){
				used2[find((i + 1) * m + j)] = 0;
				tot *= val[find((i + 1) * m + j)];
				tot %= mod;
			}
		}
		
		for(int j = 1; j < m - 1; j++){
			if(grid[i][j] && used[find(i * m + j)]){
				x1 *= val[find(i * m + j)] + 1;
				x1 %= mod;
				x2 *= val[find(i * m + j)]++;
				x2 %= mod;
				used[find(i * m + j)] = 0;
				used2[find(i * m + j)] = 1;
			}
		}
		
		ret += tot * ((mod + x1 - x2) % mod) % mod;
		ret %= mod;
	}
	
	cout << ret << endl;

	return 0;
}
