#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<int, double>

const int maxn = 2001;
int n, l;
double a[maxn][maxn];
bool used[maxn];
pi ans[maxn];

double amt(int i, double j){
	return a[i][(int)j] + fmod(j, 1) * (a[i][(int)j + 1] - a[i][(int)j]);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> l;
	
	for(int i = 0; i < n; i++)
	for(int j = 1; j <= l; j++){
		cin >> a[i][j];
		a[i][j] += a[i][j - 1];
	} 
	
	for(int i = 1; i <= n; i++){
		ans[i].second = l;
		for(int j = 0; j < n; j++){
			if(used[j]) continue;
			if(a[j][l] < a[j][l] / n + amt(j, ans[i - 1].second)){
				cout << -1 << endl;
				return 0;
			}
			
			int nx = lower_bound(a[j], a[j] + l, a[j][l] / n + amt(j, ans[i - 1].second)) - a[j] - 1;
			double nc = nx + (a[j][l] / n + amt(j, ans[i - 1].second) - a[j][nx]) / (a[j][nx + 1] - a[j][nx]);

			if(nc < ans[i].second) ans[i] = {j + 1, nc};
		}
		used[ans[i].first - 1] = 1;
	}
	
	for(int i = 1; i < n; i++) cout << (int)(ans[i].second * 1000000) << " " << 1000000 << endl;
	cout << ans[1].first;
	for(int i = 2; i <= n; i++) cout << " " << ans[i].first;
	cout << endl;

	return 0;
}