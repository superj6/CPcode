#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 210;
const int inf = 1000000007;
int opt[maxn];
int psum[maxn];
int canon[maxn*2][maxn*2];
vector<int> lparents[maxn][maxn];
vector<int> rparents[maxn][maxn];

int dp[maxn][maxn][maxn][2];

int main(){
	freopen("lightsout.in", "r", stdin);
	freopen("lightsout.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	vector<pair<long long, long long>> a(n);
	for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
	
	vector<int> s(1, 0);
	for(int i = 0; i < n; i++){
		int j = (i + 1) % n;
		int k = (i + 2) % n;
		s.push_back(abs(a[i].first - a[j].first) + abs(a[i].second - a[j].second));
		
		if((a[i].first - a[j].first) * (a[k].second - a[j].second) - 
		(a[k].first - a[j].first) * (a[i].second - a[j].second) > 0) s.push_back(-1);
		else s.push_back(-2);
	}
	s.back() = 0;
	
	for(int i = 0; i < n; i++){
		psum[i + 1] = opt[i + 1] = opt[i] + s[2 * i + 1];
	}
	opt[n] = 0;
	for(int i = n - 1; i >= 0; i--){
		opt[i] = min(opt[i], opt[i + 1] + s[2 * i + 1]);
	}
	
	for(int ln = 1; ln <= s.size(); ln++)
	for(int i = 0; i + ln <= s.size(); i++)
	for(int& j = canon[i][ln]; j < i; j++){
		if(canon[j][ln - 1] == canon[i][ln - 1] &&
		s[j + ln - 1] == s[i + ln - 1]) break;
	}
	
	for(int i = 0; i < s.size(); i += 2)
	for(int ln = 3; i + ln <= s.size(); ln += 2){
		if(i != canon[i][ln]) continue;
		
		lparents[canon[i + 2][ln - 2] / 2][ln / 2].push_back(i / 2);
		rparents[canon[i][ln - 2] / 2][ln / 2].push_back(i / 2);
	}
	
	int result = 0;
	for(int ln = n; ln >= 1; ln--)
	for(int i = 0; i + ln <= n + 1; i++){
		if(canon[2 * i][2 * ln - 1] != 2 * i) continue;
		
		int dist = psum[i + ln - 1] - psum[i];
		
		for(int strt = 0; strt < ln; strt++)
		for(int side = 0; side < 2; side++){
			if(i == 0 || i + ln == n + 1){
				dp[i][ln][strt][side] = -opt[i + strt];
				continue;
			}
			
			int lft_cst = -inf;
			for(int j : lparents[i][ln]) lft_cst = max(lft_cst, s[2 * j + 1] + dp[j][ln + 1][strt + 1][0]);
			
			int rht_cst = -inf;
			for(int j : rparents[i][ln]) rht_cst = max(rht_cst, s[2 * (j + ln) - 1] + dp[j][ln + 1][strt][1]);
			
			(side ? lft_cst : rht_cst) += dist;
			
			dp[i][ln][strt][side] = min(lft_cst, rht_cst);
			
			if(ln == 1) result = max(result, dp[i][ln][strt][side]);
		}
	}
	
	cout << result << endl;

	return 0;
}