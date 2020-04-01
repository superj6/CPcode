#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int k = 31;
int x, y;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> x >> y;
	x--, y--;
	
	int ret = 0;
	for(int i = 0; i < k; i++){
		ret += ((((x >> i) & 1) ^ ((y >> i) & 1)) << i);
	}
	
	cout << ret << endl;

	return 0;
}