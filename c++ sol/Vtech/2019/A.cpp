#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1000000;
int n;
long long a[maxn];
unordered_map<long long, int> used;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		if(i) a[i] += a[i - 1];
	}
	
	for(int i = 0; i < n; i++){
		if(a[i] % 2 == 0 && a[i] * 3 / 2 == a[n - 1] && used[a[i] / 2]){
			cout << used[a[i] / 2] << " " << i + 1 << endl;
			return 0;
		}
		used[a[i]] = i + 1;
	}
	
	cout << -1 << endl;

	return 0;
}