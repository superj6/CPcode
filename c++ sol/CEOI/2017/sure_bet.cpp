#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100001;
int n;
double a[maxn], b[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(4);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++) cin >> a[i] >> b[i];
	
	sort(a + 1, a + n + 1, greater<double>());
	sort(b + 1, b + n + 1, greater<double>());
	
	double ret = 0;
	for(int i = 1, j = 1; i <= n; i++){
		a[i] += a[i - 1];
		while(j < n && b[j] < a[i]) b[++j] += b[j - 1];
		ret = max(ret, min(a[i], b[j]) - i - j);
		if(j) ret = max(ret, min(a[i], b[j - 1]) - i - j + 1);
	}
	
	cout << ret << endl;

	return 0;
}