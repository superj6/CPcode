#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100000;
int n;
int a[maxn], b[maxn];

void answer(){
    cin >> n;
    
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < n; i++) cin >> b[i];
	
	int ret = 0;
	for(int i = 0; i < n; i++){
	    ret ^= ((n - (b[i] - a[i] + 1)) & 1);
	}
	
	cout << (ret ? "WHITE" : "BLACK") << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}