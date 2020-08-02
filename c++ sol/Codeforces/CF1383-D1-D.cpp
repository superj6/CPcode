/*
  Realize each element in spectrum will need to use new row if they are largest in column and new column if they are largest in row,
so find all largest elements begin placing every element from the top left corner in decreasing order, moving to a new row or new column
if it is on the spectrum. Now to add non-spectrum elements, hold a queue of positions to add, and when you add a spectrum element add
all positions in decreasing order in the new row or column used below the newly added spectrum element. Because spectrum elements are
going from top left to bottom right the decreasing part of bitonic condition will always hold, and because you positions to queue in
decreasing order in row or column the bitonic condition will always hold for increasing part, and because your adding element in decreasing
order the largest will always be the spectrum element first added to the row or column. This shwos you can always construct a solution.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 250;
int n, m;
int a[mxn][mxn];
int mx[mxn * mxn], my[mxn * mxn];
int qx[mxn * mxn], qy[mxn * mxn];
int fx[mxn * mxn], fy[mxn * mxn];
int ql, qr;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		int x;
		cin >> x;
		x--;
		mx[i] = max(mx[i], x);
		my[j] = max(my[j], x);
	}
	
	for(int i = 0; i < n; i++) fx[mx[i]] = 1;
	for(int i = 0; i < m; i++) fy[my[i]] = 1;
	
	for(int i = n * m - 1, x = -1, y = -1; ~i; i--){
		x += fx[i], y += fy[i];
		if(fx[i] || fy[i]) a[x][y] = i + 1;
		else a[qx[ql]][qy[ql]] = i + 1, ql++;
		if(fx[i]) for(int j = y - 1; ~j; j--) qx[qr] = x, qy[qr] = j, qr++;
		if(fy[i]) for(int j = x - 1; ~j; j--) qx[qr] = j, qy[qr] = y, qr++;
	}
	
	for(int i = 0; i < n; i++){
		cout << a[i][0];
		for(int j = 1; j < m; j++) cout << " " << a[i][j];
		cout << endl;
	}

	return 0;
}
