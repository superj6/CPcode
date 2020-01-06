#include <iostream>
#include <cstdio>
#include <algorithm>
#include <trilib.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 50;
int n;
bool works[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	n = get_n();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j) continue;
			bool t = 1;
			for(int k = 0; k < n; k++){
				if(k == i || k == j) continue;
				t &= is_clockwise(i, j, k);
			}
			works[i] |= t;
			works[j] |= t;
		}
	}
	
	int ret = 0;
	for(int i = 0; i < n; i++) ret += works[i];
	give_answer(ret);

	return 0;
}