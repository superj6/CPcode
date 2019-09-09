#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define endl '\n'

typedef pair<int, int> pii;
typedef vector<int> vi;

struct rs{
	int v[2];
};

static const int bias = 128;
static int tree[2][2 * bias][2 * bias], orig_tree[2][2 * bias][2 * bias];

static vector<int> make_split(int a, int b){
	vector<int> ans;
	a += bias;
	b += bias;
	
	while(a < b){
		if(a & 1){
			ans.push_back(a);
			a++;
		}
		if(b & 1){
			b--;
			ans.push_back(b);
		}
		a /= 2;
		b /= 2;
	}
	
	return ans;
}

static void findo(int x, int r, int c, vector<pii> &out){
	if(tree[x][r][c]){
		if(c < bias){
			findo(x, r, 2 * c, out);
			findo(x, r, 2 * c + 1, out);
		}else if(r < bias){
			findo(x, 2 * r, c, out);
			findo(x, 2 * r + 1, c, out);
		}else{
			out.push_back(pii(r, c));
		}
	}
}

int main(){
	freopen("skicourse.in", "r", stdin);
	freopen("skicourse.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int r, c;
	cin >> r >> c;
	
	for(int i = 0; i < r; i++){
		string line;
		cin >> line;
		for(int j = 0; j < c; j++){
			int idx = (line[j] == 'S');
			tree[idx][i + bias][j + bias] = 1;
		}
	}
	
	for(int idx = 0; idx < 2; idx++){
		for(int i = 2 * bias - 1; i > 0; i--){
			for(int j = 2 * bias - 1; j > 0; j--){
				if(i < bias){
					tree[idx][i][j] = tree[idx][2 * i][j] + tree[idx][2 * i + 1][j];
				}else if(j < bias){
					tree[idx][i][j] = tree[idx][i][2 * j] + tree[idx][i][2 * j + 1];
				}
				
			}
		}
	}
	memcpy(orig_tree, tree, sizeof(tree));
	
	int lo = 1;
	int hi = min(r, c) + 1;
	while(hi - lo > 1){
		memcpy(tree, orig_tree, sizeof(tree));
		int b = (lo + hi) / 2;
		vector<pair<vi, vi>> sites;
		vector<int> rev[2 * bias][2 * bias];
		vector<rs> wait;
		queue<int> active;
		
		for(int i = 0; i + b <= r; i++){
			for(int j = 0; j + b <= c; j++){
				vi rows = make_split(i, i + b);
				vi cols = make_split(j, j + b);
				rs w = {{0, 0}};
				
				for(int x = 0; x < 2; x++){
					for(size_t k = 0; k < rows.size(); k++){
						for(size_t l = 0; l < cols.size(); l++){
							w.v[x] += tree[x][rows[k]][cols[l]];
							
							if(x == 0){
								rev[rows[k]][cols[l]].push_back(sites.size());
							}
						}
					}
				}
				
				wait.push_back(w);
				if(w.v[0] == 0 || w.v[1] == 0){
					active.push(sites.size());
				}
				sites.push_back(make_pair(rows, cols));
			}
		}
		
		while(!active.empty()){
			int b1 = active.front();
			active.pop();
			
			const vi &rows = sites[b1].first;
			const vi &cols = sites[b1].second;
			for(size_t i = 0; i < rows.size(); i++){
				for(size_t j = 0; j < cols.size(); j++){
					int ri = rows[i];
					int cj = cols[j];
					
					for(int x = 0; x < 2; x++){
						vector<pii> wipe;
						findo(x, ri, cj, wipe);
						
						for(size_t k = 0; k < wipe.size(); k++){
							for(int p = wipe[k].first; p > 0; p >>= 1){
								for(int q = wipe[k].second; q > 0; q >>= 1){
									--tree[x][p][q];
									
									for(size_t l = 0; l < rev[p][q].size(); l++){
										int b2 = rev[p][q][l];
										if(--wait[b2].v[x] == 0 && wait[b2].v[!x] > 0){
											active.push(b2);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		
		if(tree[0][1][1] == 0 && tree[1][1][1] == 0){
			lo = b;
		}else{
			hi = b;
		}
	}
	
	cout << lo << endl;

	return 0;
}