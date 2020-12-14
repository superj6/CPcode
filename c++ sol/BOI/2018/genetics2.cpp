#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
#define ull unsigned long long

const int maxn = 4101, w = 4, b = 33;
int n, m, k;
int a[maxn][maxn];
ull p[maxn];
ull	ss[maxn][w];
ull f, g;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	p[0] = 1;
	for(int i = 1; i <= n; i++){
		string s;
		cin >> s;
		
		p[i] = b * p[i - 1];
		f += p[i], g += k * p[i];
		for(int j = 0; j < m; j++){
			a[i][j] = (s[j] == 'A' ? 0 : s[j] == 'C' ? 1 : s[j] == 'G' ? 2 : 3);
			ss[j][a[i][j]] += p[i];
		}
	}
	
	for(int i = 1; i <= n; i++){
		ull c = 0;
		for(int j = 0; j < m; j++) c += f - ss[j][a[i][j]];
		if(g == c + k * p[i]){
			cout << i << endl;
			return 0;
		}
	}

	return 0;
}