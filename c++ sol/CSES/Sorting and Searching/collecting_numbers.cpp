#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200001;
int n;
int a[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	
	int ret = n;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		ret -= a[x - 1], a[x] = 1;
	}
	
	cout << ret << endl;

	return 0;
}