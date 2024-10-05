#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 998244353;
const int mxn = 100001, w = 10;
int n, k;
int a[mxn];
pi dp[mxn][w][2]; //{clamp, mod}
string s;
vector<int> v;

pi operator+(pi x, pi y){
  return {min(mod, x.f + y.f), (x.s + y.s) % mod};
}

bool valid_num(int x){
  return x >= 1 && x <= 26;
}

void compute_dp(){
  for(int j = 0; j < w; j++){
    dp[n][j][0] = dp[n][j][1] = {0, 0};
  } 

  dp[n][0][1] = {1, 1};
  for(int i = n - 1; ~i; i--)
  for(int j = 0; j < w; j++){
    dp[i][j][0] = dp[i][j][1] = {0, 0};
    for(int l = 0; l < w; l++){
      dp[i][j][0] = dp[i][j][0] + dp[i + 1][l][1];
      if(valid_num(j)){
        dp[i][j][1] + dp[i][j][1] + dp[i + 1][l][1];
      }
      if(valid_num(j * w + l)){
        dp[i][j][1] = dp[i][j][1] + dp[i + 1][l][0];
      }
    }
  }
}

void compute_kth(){
  int cur[w][2], old_cur[w][2];
  for(int j = 0; j < w; j++){
    cur[j][0] = 0;
    cur[j][1] = 1;
  }

  int z = 0;
  for(int i = 0, prev_dig = 0, fin_state = 1; i < n; i++){
    for(int j = 0; j < w; j++){
      int zz = 0;
      for(int x = 0; x < 2; x++){
        zz = min((ll)mod, zz + (ll)cur[j][x] * dp[i][j][x].f);
      }

      if(z + zz > k){
        v.push_back(j);

        memcpy(old_cur, cur, sizeof(cur));
        memset(cur, 0, sizeof(cur));
        for(int l = 0; l < w; l++){
          cur[l][1] += old_cur[j][0];
          if(valid_num(j)){
            cur[l][1] += old_cur[j][1];
          }
          if(valid_num(j * w + l)){
            cur[l][1] += old_cur[j][0];
          }
        }
        break;
      }

      z += zz;
    }
  }
}

void answer(){
  cin >> s >> k;
  n = s.size(), k--;

  for(int i = 0; i < n; i++){
    a[i] = s[i] - '0';
  }

  compute_dp();
  compute_kth();

  int ret_cnt = 0;
  for(int j = 0; j < w; j++) (ret_cnt += dp[0][j][1].s) %= mod;

  for(int i : v) cout << i;
  cout << " " << ret_cnt << endl;
}

int main(){
  freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for(int i = 1; i <= t; i++){
		cout << "Case #" << i << ": ";
		answer();
	}
	
	return 0;
}
