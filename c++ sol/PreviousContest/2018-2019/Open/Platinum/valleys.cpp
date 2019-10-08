#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define pii pair<int, pair<int, int>>

const int maxn = 750;
int n;
int a[maxn][maxn];
bool used[maxn][maxn];
pii h[maxn * maxn];

int par[maxn * maxn];
int rnk[maxn * maxn];
int cnt[maxn * maxn];
int sz[maxn * maxn];

int dx[9] = {1, 1, 0, -1, -1, -1, 0, 1, 0};
int dy[9] = {0, 1, 1, 1, 0, -1, -1, -1, 0};

int find(int x){
        return x == par[x] ? x : par[x] = find(par[x]);
}

void unionf(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return;

        if(rnk[x] < rnk[y]) swap(x, y);
        if(rnk[x] == rnk[y]) rnk[x]++;
        par[y] = x;
        cnt[x] += cnt[y];
        sz[x] += sz[y];
}

bool works(int x, int y){
        if(x < 0 || x >= n || y < 0 || y >= n) return 0;
        if(!used[x][y]) return 0;
        return 1;
}

void chg(int p, int v){
        int x = h[p].second.first, y = h[p].second.second;
        p = find(p);
        for(int i = 0; i < 8; i += 2){
                bool w[3];
                for(int j = 0; j < 3; j++){
                        w[j] = works(x + dx[(i + j) % 8], y + dy[(i + j) % 8]);
                }

                if(!w[0] && !w[2]) cnt[p] += v;
                else if(w[0] && w[2] && !w[1]) cnt[p] -= v;
        }
}

long long solve(int p){
        int x = h[p].second.first, y = h[p].second.second;
        for(int i = 0; i < 8; i++){
                if(!works(x + dx[i],y + dy[i])) continue;
                int np = a[x + dx[i]][y + dy[i]];
                chg(np, -1);
                if(i % 2 == 0) unionf(p, np);
        }

        p = find(p);
        used[x][y] = 1;

        for(int i = 0; i < 9; i++){
                if(!works(x + dx[i],y + dy[i])) continue;
                int np = a[x + dx[i]][y + dy[i]];
                chg(np, 1);
        }

        return cnt[p] == 4 ? sz[p] : 0;
}

int main() {
        freopen("valleys.in", "r", stdin);
        freopen("valleys.out", "w", stdout);
        ios::sync_with_stdio(0);
        cin.tie(0);

        cin >> n;

        for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                        cin >> h[i * n + j].first;
                        h[i * n + j].second = {i, j};
                }
        }

        sort(h, h + n * n);

        for(int i = 0; i < n * n; i++){
                a[h[i].second.first][h[i].second.second] = i;
                par[i] = i;
                sz[i] = 1;
        }

        long long ret = 0;
        for(int i = 0; i < n * n; i++) ret += solve(i);

        cout << ret << endl;

        return 0;
}