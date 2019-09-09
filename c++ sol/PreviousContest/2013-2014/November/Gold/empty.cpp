#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

long long n, k;

int parent[3000000];

int find(int x){
	return (parent[x] == x) ? x : find(parent[x]);
}

void unionnext(int x){
	int rootx = find(x);
	int rooty = find((rootx + 1) % n);
	
	parent[rootx] = rooty;
}

int main(){
	freopen("empty.in", "r", stdin);
	freopen("empty.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++) parent[i] = i;
	
	for(int i = 0; i < k; i++){
		long long x, y, a, b;
		cin >> x >> y >> a >> b;
		
		for(int j = 1; j <= y; j++){
			int num = (j * a + b) % n;
			for(int k = 0; k < x; k++){
				unionnext(num);
				//for(int i = 0; i < n; i++) cout << find(i) << " ";
				//cout << endl;
			}
		}
	}
	
	cout << find(0) << endl;

	return 0;
}