#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 750, mod = 1000000007;
int r, c, k;
int grid[maxn][maxn];

struct BIT{
	vector<int> indices;
	vector<int> tree;
	
	BIT(vector<int> set){
		indices.push_back(-1);
		tree.push_back(0);
		
		for(int out : set){
			indices.push_back(out);
			tree.push_back(0);
		}
		
		tree.push_back(0);
		indices.push_back(maxn);
	}
	
	void update(int index, int val){
		int actual = lower_bound(indices.begin(), indices.end(), index) - indices.begin();
		
		while(actual < tree.size() - 1){
			tree[actual] += val;
			if(tree[actual] >= mod) tree[actual] -= mod;
			actual += actual & (-actual);
		}
	}
	
	int query(int index){
		int actual = prev(upper_bound(indices.begin(), indices.end(), index)) - indices.begin();
		
		int res = 0;
		while(actual > 0){
			res += tree[actual];
			if(res >= mod) res -= mod;
			actual -= actual & (-actual);
		}
		
		return res;
	}
};

int main(){
	freopen("hopscotch.in", "r", stdin);
	freopen("hopscotch.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> r >> c >> k;
	
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			cin >> grid[i][j];
		}
	}
	
	vector<int> columns[k + 1];
	
	for(int j = 0; j < c; j++){
		for(int i = 0; i < r; i++){
			if(!columns[grid[i][j]].empty() && columns[grid[i][j]].back() == j) continue;
			columns[grid[i][j]].push_back(j);
		}
	}
	
	vector<int> gen;
	vector<BIT> bits;
	bits.push_back(BIT(gen));
	
	for(int a = 1; a <= k; a++){
		bits.push_back(BIT(columns[a]));
	}
	
	for(int i = 0; i < c; i++) gen.push_back(i);
	
	BIT full = BIT(gen);
	full.update(0, 1);
	bits[grid[0][0]].update(0, 1);
	
	for(int i = 1; i < r - 1; i++){
		for(int j = c - 2; j > 0; j--){
			long val = full.query(j - 1) - bits[grid[i][j]].query(j - 1);
			if(val < 0) val += mod;
			full.update(j, val);
			bits[grid[i][j]].update(j, val);
		}
	}
	
	int ans = full.query(c - 2) - bits[grid[r - 1][c - 1]].query(c - 2);
	if(ans < 0) ans += mod;
	
	cout << ans << endl;

	return 0;
}