#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1000000007;
const int maxn = 1000000;
int n, m;
pi p[maxn];
int a[maxn], b[maxn];
long long dp[maxn];
set<int> used;
vector<int> l, r;

void answer(){
	cin >> m >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i] >> b[i];
		p[i] = {a[i], i + 1};
		p[i + n] = {b[i], -i - 1};
	}
	n = 2 * n;
	sort(p, p + n);
	
	l.clear(), r.clear();
	memset(dp, 0, sizeof(dp));
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < n; i++){
			if(p[i].second < 0){
				if(used.find(p[i].second) != used.end()){
					if(t) l.push_back(n - i - 1);
					else r.push_back(i - 1);
					used.clear();
				}
			}else{
				used.insert(-p[i].second);
			}
			p[i].first *= -1;
			p[i].second *= -1;
		}
		reverse(p, p + n);
	}
	reverse(l.begin(), l.end());
	
	n = l.size();
	for(int i = 0; i < n; i++){
		if(i){
			for(int j = l[i], k = l[i - 1]; j <= r[i]; j++){
				if(p[j].second < 0) while(p[k].first < a[-p[j].second - 1]) k++;
				dp[j] += dp[k] * (p[j + 1].first - p[j].first);
				dp[j] %= mod;
			}
		}else{
			for(int j = l[i]; j <= r[i]; j++) dp[j] = p[j + 1].first - p[j].first;
		}
		
		for(int j = r[i] - 1; j >= l[i]; j--){
			dp[j] += dp[j + 1];
			dp[j] %= mod;
		} 
	}
	
	cout << n << " " << dp[l.back()] << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int z;
	cin >> z;
	
	for(int i = 0; i < z; i++) answer();

	return 0;
}