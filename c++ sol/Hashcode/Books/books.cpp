#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define ll long long

const int maxn = 100000;
int n, m, k; //books, libraries, days
ll a[maxn]; //book scores
ll s[maxn]; //library signup times
ll r[maxn]; //library shipping rate in books per day
vector<int> b[maxn]; //books in each library
vector<int> lib[maxn]; //libraries containing book

const ll mult = 100000000; //multiply stuff so not decimal
int lft;
ll p[maxn]; //probability book will be used
ll rnk[maxn]; //rank score of books
bool usedlib[maxn]; //tell if library used
bool usedbk[maxn]; //tell if book used

int amt = 0;
int ans[maxn];
vector<int> ansb[maxn];

bool sortrnk(int a, int b){
	return rnk[a] > rnk[b];
}

int main(){
	freopen("./input/f_libraries_of_the_world.txt", "r", stdin);
	freopen("./output/output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;

	for(int i = 0; i < n; i++) cin >> a[i];

	for(int i = 0; i < m; i++){
		int l;
		cin >> l >> s[i] >> r[i];

		b[i].resize(l);
		for(int j = 0; j < l; j++){
			cin >> b[i][j];
			lib[b[i][j]].push_back(i);
		} 
	}

	ll ret = 0;
	lft = n;
	while(k){
		for(int i = 0; i < m; i++){
			if(k <= s[i] && !usedlib[i]){
				lft--;
				usedlib[i] = 1;
				for(int j : b[i]){
					lib[j].erase(remove(lib[j].begin(), lib[j].end(), i), lib[j].end());
					if(lib[j].empty()) usedbk[j] = 1;
				}
			}
		}

		if(!lft) break;

		for(int i = 0; i < n; i++){
			if(usedbk[i]) continue;
			for(int j : lib[i]){
				int scnd = min((k - s[j]) * r[j], (ll)b[j].size());
				p[i] += mult * scnd / (b[j].size());
			}
			p[i] /= lft;
			rnk[i] = a[i] * (mult - p[i]);
		}

		ll bs = 0, bi = -1;
		for(int i = 0; i < m; i++){
			if(usedlib[i]) continue;
			sort(b[i].begin(), b[i].end(), sortrnk);\

			int scnd = min((k - s[i]) * r[i], (ll)b[i].size());
			ll cur = 0;
			for(int j = 0; j < scnd; j++){
				cur += a[b[i][j]];
			}
			
			if(cur > bs){
				bs = cur;
				bi = i;
			}
		}

		if(bi == -1) break;

		for(int i = 0; i < min((k - s[bi]) * r[bi], (ll)b[bi].size()); i++){
			int j = b[bi][i];
			ansb[amt].push_back(j);
			usedbk[j] = 1;
			for(int l : lib[j]){
				if(l == bi) continue;
				b[l].erase(remove(b[l].begin(), b[l].end(), j), b[l].end());
			}
		}

		ret += bs;
		k -= s[bi];
		usedlib[bi] = 1;
		ans[amt++] = bi;
		lft--;
	}

	cout << ret << endl;
	cout << endl;

	cout << amt << endl;
	for(int i = 0; i < amt; i++){
		cout << ans[i] << " " << ansb[i].size() << endl;
		for(int j : ansb[i]) cout << j << " ";
		cout << endl;
	}

	return 0;
} 