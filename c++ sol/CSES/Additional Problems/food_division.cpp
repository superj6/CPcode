#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 200001;
int n;
long long a[maxn];
long long sum;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		a[i] += a[i - 1] - x;
		sum += a[i];
	}
		
	sort(a + 1, a + n + 1);
	
	long long ret = 1000000000000007;
	for(long long i = 1, s = 0; i <= n; i++){
		s += a[i];
		ret = min(ret, sum - 2 * s + (2 * i - n) * a[i]);
	}
	
	cout << ret << endl;

	return 0;
}