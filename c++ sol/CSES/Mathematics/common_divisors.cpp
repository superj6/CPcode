#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1000001;
int n;
int cnt[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		cnt[x]++;
	}
	
	for(int i = maxn - 1; i > 0; i--){
		int cur = 0;
		
		for(int j = i; j < maxn; j += i){
			cur += cnt[j];
			if(cur > 1){
				cout << i << endl;
				return 0;
			}
		}
	}

	return 0;
}