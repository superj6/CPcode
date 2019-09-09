#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 100000, maxd = 10;
const int maxt = maxn * maxd;

long long n, x, y, z;
vector<int> dirt[2 * maxt + 1];
int type[2 * maxt + 1];
long long res1[2 * maxt + 1], res2[2 * maxt + 1];

void dp(vector<int> &v, long long *res){
	long long m = v.size(), i = -2, ci = 0, cj = 0, prev = 100000000000007;
	for(int j = 1; j < m; j += 2){
		if(j > 1){
			cj += z * abs(v[j - 2] - v[j - 1]);
			prev += z * abs(v[j - 2] - v[j - 1]);
		} 
		while(i + 2 < j && x + y <= z * abs(v[j] - v[i + 2])){
			i += 2;
			if(i > 0) ci += z * abs(v[i] - v[i - 1]);
			prev = min(prev, x + y + cj - ci + (i > 0 ? res[i - 1] : 0));
		}
		res[j] = min(prev, z * abs(v[j] - v[j - 1]) + (j > 1 ? res[j - 2] : 0));
	}
}

long long solve(vector<int> &v, long long ecost){
	int m = v.size();
	if(m == 0) return 0;
	if(m == 1) return ecost;
	
	dp(v, res1);
	reverse(v.begin(), v.end());
	dp(v, res2);
	reverse(res2, res2 + m);
	
	if(m % 2 == 0) return res1[m - 1];
	
	long long best = min(res1[m - 2], res2[1]);
	for(int i = 2; i <= m - 3; i += 2) best = min(best, res1[i - 1] + res2[i + 1]);
	
	return best + ecost;
}

int main(){
	freopen("landscape.in", "r", stdin);
	freopen("landscape.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> x >> y >> z;
	
	int l = maxt, p = 0;

	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		
		int t = (max(a, b) == a ? 1 : -1);
		int d = abs(a - b);
		
		if(p != t) l += t;
		while(d-- > 0){
			dirt[l].push_back(i);
			type[l] = t;
			l += t;
		}
		
		p = t;
	}
	
	long long total = 0;
	
	for(int i = 0; i <= 2 * maxt; i++) total += solve(dirt[i], (type[i] == 1 ? y : x));
	
	cout << total << endl;

	return 0;
}