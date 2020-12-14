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

const int maxn = 100;
int n;
int a[maxn][maxn], b[maxn][maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		cin >> a[i][j];
	}
	
	for(int t = 0; t < 4; t++){
		if(a[0][0] < a[0][1] && a[0][0] < a[1][0]){
			for(int i = 0; i < n; i++){
				cout << a[i][0];
				for(int j = 1; j < n; j++) cout << " " << a[i][j];
				cout << endl;
			}
			break;
		}
		memcpy(b, a, sizeof(a));
		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			a[i][j] = b[n - j - 1][i];
		}
	}

	return 0;
}