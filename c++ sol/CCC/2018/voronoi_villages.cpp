#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100;
int n;
int a[maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(1);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	
	double ret = a[n - 1] - a[0];
	for(int i = 1; i < n - 1; i++){
		ret = min(ret, (a[i + 1] - a[i - 1]) / 2.0);
	}
	
	cout << ret << endl;

	return 0;
}