#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000002;
int n;
int a[mxn], f1[mxn], f2[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	a[0] = -1, a[n + 1] = 1;
	for(int i = 1, j = 0; i <= n; i++){
		cin >> a[i];
		f1[i] += 1 + a[i] + f1[i - 1];
		if(!~a[i] && !a[i - 1] && !j){
			cout << "BRAK" << endl;
			return 0;
		}
		j |= !!a[i];
	}
	
	for(int i = n; i; i--) f2[i] += 1 - a[i] + f2[i + 1];
	
	int ret = 2 * n;
	for(int i = 1, j = 0; i <= n + 1; i++){
		if(!~-a[i]){
			if(!j){
				ret = min(ret, f2[i]);
			}else if(!~a[1]){
				ret = min(ret, f1[j] + f2[i] - !~-a[j]);
			}
		}
		if(a[i]) j = i;
	}
	
	cout << ret << endl;

	return 0;
}