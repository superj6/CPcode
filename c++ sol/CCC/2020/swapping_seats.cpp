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

const int maxn = 2000001, k = 4;
int n;
string s;
int a[k][maxn];
int b[k];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	n = s.size();
	
	int ret = 3 * n;
	for(int tt = 0; tt < 2; tt++){
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		for(int i = 0; i < n; i++){
			int t = s[i] - 'A' + 1;
			a[t][i + 1] = a[t][n + i + 1] = 1;
			b[t]++;
		}
		
		for(int t = 1; t < k; t++){
			b[t] += b[t - 1];
			for(int i = 1; i <= 2 * n; i++){
				a[t][i] += a[t][i - 1];
			}
		}
		
		for(int i = 0; i < n; i++){
			int cur = 0, c = n;
			b[0]++;
			for(int j = 1; j < k; j++){
				b[j]++;
				c -= a[j][b[j]] - a[j][b[j - 1]];
				for(int l = 1; l < j; l++){
					cur += min(a[j][b[l]] - a[j][b[l - 1]], a[l][b[j]] - a[l][b[j - 1]]);
				}
			}
			
			c -= 2 * cur;
			cur += c / 3 * 2;
			ret = min(ret, cur);
		}
		
		reverse(s.begin(), s.end());
	}
	
	cout << ret << endl;

	return 0;
}