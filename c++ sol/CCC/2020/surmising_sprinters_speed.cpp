#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100000;
int n;
pi a[maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(5);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i].f >> a[i].s;
	
	sort(a, a + n);
	
	double ret = 0;
	for(int i = 1; i < n; i++){
		ret = max(ret, abs(1.0 * (a[i].s - a[i - 1].s) / (a[i].f - a[i - 1].f)));
	}
	
	cout << ret << endl;

	return 0;
}