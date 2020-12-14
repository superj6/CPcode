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

const int mxn = 8001;
int n;
int a[mxn];
int s[mxn][2];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= 2 * n; i++){
		char c;
		cin >> c;
		a[i] = a[i + 2 * n] = c == 'B' ? 0 : 1;
	}
	
	for(int i = 1; i <= 4 * n; i++){
		memcpy(s[i], s[i - 1], sizeof(s[i]));
		s[i][a[i]]++;
	}
	
	ll ret = 0;
	for(int t = 1; t <= 2 * n; t++){
		ll cur = 0;
		for(int i = 0, j = n, l = n; i < n; i++){
			if(a[t + i]){
				while(a[t + j]) j++;
				cur += s[t + 2 * n - 1][0] - s[t + j][0];
				cur += s[t + 2 * n - 1][1] - s[t + max(j, l - 1)][1];
				j++;
			}else{
				while(!a[t + l]) l++;
				cur += s[t + 2 * n - 1][1] - s[t + l][1];
				cur += s[t + 2 * n - 1][0] - s[t + max(j - 1, l)][0];
				l++;
			}
		}
		ret = max(ret, cur);
	}
	
	cout << ret << endl;

	return 0;
}