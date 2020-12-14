#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
const int maxn = 100;
int n, m, a, b, sx, sy;
int d[maxn][maxn];
queue<pi> q;
int dx[4] = {1, 1, -1, -1};
int dy[4] = {1, -1, 1, -1};

bool works(int x, int y){
    return (x >= 0 && y >= 0 && x < n && y < m);
}

int val(int x){
    return x == inf ? -1 : x;
}

void answer(){
	cin >> n >> m >> a >> b >> sx >> sy;
	sx--, sy--;
	
	memset(d, inf, sizeof(d));
	d[sx][sy] = 0;
	q.push({sx, sy});
    while(!q.empty()){
        int x = q.front().f, y = q.front().s;
        q.pop();
        for(int t = 0; t < 2; t++){
            for(int i = 0; i < 4; i++){
                int nx = x + a * dx[i], ny = y + b * dy[i];
                if(works(nx, ny) && d[nx][ny] == inf){
                    d[nx][ny] = d[x][y] + 1;
                    q.push({nx, ny});
                }
            }
            swap(a, b);
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << val(d[i][j]);
	    if(j < m - 1) cout << " ";
        }
        cout << endl;
    }
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}