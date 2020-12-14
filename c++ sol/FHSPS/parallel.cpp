#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 900;
int n;
char a[maxn][maxn];
int was[maxn], pa[maxn], pb[maxn];
vector<int> g[maxn];
int it = 0;
 
bool dfs(int c){
	was[c] = it;
	
	for(int i : g[c]){
		if(pb[i] == -1){
			pa[c] = i;
			pb[i] = c;
			return 1;
		}
	}
	
	for(int i : g[c]){
		if(was[pb[i]] != it && dfs(pb[i])){
			pa[c] = i;
			pb[i] = c;
			return 1;
		}
	}
	
	return 0;
}
 
int solve(){
    it = 0;
	int ret = 0, add;
	memset(pa, -1, sizeof(pa));
	memset(pb, -1, sizeof(pb));
	
	do{
		add = 0;
		it++;
		
		for(int i = 0; i < n; i++){
			if(pa[i] == -1 && dfs(i)) add++;
		}
		
		ret += add;
	} while(add);
	
	return ret;
}

void answer(){
	cin >> n;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
	    cin >> a[i][j];
	    g[i * n + j].clear();
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int x = 0; x < n; x++)
	for(int y = 0; y < n; y++){
	    bool t = 0;
	    int s = abs(x - i) + abs(y - j);
	    t |= s == 3 && (abs(x - i) == 1 || abs(y - j) == 1) && a[i][j] == 'N';
	    t |= abs(x - i) == abs(y - j) && ((s == 2 && a[i][j] == 'K') || a[i][j] == 'B' || a[i][j] == 'Q');
	    t |= (x == i || y == j) && ((s == 1 && a[i][j] == 'K') || a[i][j] == 'R' || a[i][j] == 'Q');
	    if(t && a[x][y] == '.') g[i * n + j].push_back(x * n + y);
	}
	n *= n;
	
	cout << solve() << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}