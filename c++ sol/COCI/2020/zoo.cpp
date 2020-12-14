#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
pi operator+(pi a, pi b){
    return {a.f + b.f, a.s + b.s};
}
 
const int maxn = 1000;
int n, m;
int a[maxn][maxn];
queue<pi> q[2];
pi d[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
 
bool ok(pi p){
    return p.f >= 0 && p.s >= 0 && p.f < n && p.s < m && a[p.f][p.s] != -1;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
	    char c;
	    cin >> c;
	    a[i][j] = c == '*' ? -1 : c == 'B';
	}
	
	int ret = 0;
	q[a[0][0]].push({0, 0});
	for(int t = a[0][0]; !q[t].empty(); t ^= 1, ret++){
	    while(!q[t].empty()){
	        pi p = q[t].front();
	        q[t].pop();
	        for(int i = 0; i < 4; i++){
	            pi np = p + d[i];
	            if(ok(np)){
	                q[a[np.f][np.s]].push(np);
	                a[np.f][np.s] = -1;
	            }
	        }
	    }
	}
	
	cout << ret << endl;
 
	return 0;
}