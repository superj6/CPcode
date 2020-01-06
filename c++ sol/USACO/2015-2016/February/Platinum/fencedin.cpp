#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	freopen("fencedin.in", "r", stdin);
	freopen("fencedin.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long A, B, n, m;
	cin >> A >> B >> n >> m;
	
	long long a[n + 1], b[m + 1];
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++) cin >> b[i];
	a[n] = A, b[m] = B;
	
	sort(a, a + n);
	sort(b, b + m);
	
	for(int i = n; i > 0; i--) a[i] = a[i] - a[i - 1]; 
	for(int i = m; i > 0; i--) b[i] = b[i] - b[i - 1]; 
	
	n++, m++;
	sort(a, a + n);
	sort(b, b + m);
	
	long long ret = a[0] * (m - 1) + b[0] * (n - 1);
	
	for(int ai = 1, bi = 1; ai < n && bi < m;){
		if(a[ai] < b[bi]){
			ret += a[ai] * (m - bi);
			ai++;
		}else{
			ret += b[bi] * (n - ai);
			bi++;
		}
	}
	
	cout << ret << endl;

	return 0;
}