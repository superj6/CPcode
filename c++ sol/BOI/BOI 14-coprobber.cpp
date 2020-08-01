/*
  Think about graph of all states which are where cop is, where robber is, and who's turn it is. You then want to find all reachable
winning states and if there is no state on cops turn where robber cop cannot win you can start from any position. If you are on state 
where it is robber's turn, you can move the cop along any edge or keep it in place since you will be moving to state that is cop's 
turn. If you are on state where it is cop's turn, you can move robber back along any edge such that if the robber were to move along
any edge from its new vertex it would still be a winning state for a cop. To see if that's the case, you can do something similar to
topo sort where you hold how many adjacent states have still not been reached to see if you can transition to a state on robbers turn.
Obviously you can start topo sort with all states such that the cop and robbers position are the same, and when moving the cop you can
hold the transition to use when simulating the chase.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

typedef array<int, 3> T;

const int mxn = 500;
int c;
int d[mxn][mxn], f[mxn][mxn];
bool vis[mxn][mxn][2];
queue<T> q;

int start(int n, bool g[mxn][mxn]){
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int k = 0; k < n; k++){
		d[i][j] += g[j][k];
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < 2; j++){
		vis[i][i][j] = 1;
		q.push({i, i, j});
	}
	
	while(!q.empty()){
		T a = q.front();
		q.pop();
		for(int i = 0; i < n; i++){
			if(a[2] && (g[a[0]][i] || i == a[0]) && !vis[i][a[1]][0]){
				vis[i][a[1]][0] = 1;
				q.push({i, a[1], 0});
				f[i][a[1]] = a[0];
			}else if(!a[2] && g[a[1]][i] && !vis[a[0]][i][1] && --d[a[0]][i] <= 0){
				vis[a[0]][i][1] = 1;
				q.push({a[0], i, 1});
			}
		}	
	}
	
	for(int i = 0; i < n; i++) if(!vis[0][i][0]) return -1;
	return 0;
}

int nextMove(int r){
	return c = f[c][r];
}
