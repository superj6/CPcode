#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 3001;
int n, m;
string s[maxn];
int a[maxn][maxn], b[maxn][maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
	    cin >> s[i];
	    for(int j = 0; j < m; j++){
	        if(s[i][j] == 'O') a[i][j]++;
	        if(s[i][j] == 'I') b[i][j]++;
	    }
	}
	
	ll ret = 0;
	for(int i = n - 1; ~i; i--)
	for(int j = m - 1; ~j; j--){
	    a[i][j] += a[i][j + 1];
	    b[i][j] += b[i + 1][j];
	    ret += (s[i][j] == 'J') * a[i][j] * b[i][j];
	}
	
	cout << ret << endl;

	return 0;
}