#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

char grid[8][8];
int used[8];

int amt(int cur){
	if(cur == 8) return 1;
	
	int works[8];
	for(int i = 0; i < 8; i++) works[i] = 1;
	
	for(int i = 0; i < 8; i++){
		if(used[i] == -1) continue;
		if(i + cur - used[i] < 8) works[i + cur - used[i]] = 0;
		if(i - cur + used[i] >= 0) works[i - cur + used[i]] = 0;
	}
	
	int ret = 0;
	
	for(int i = 0; i < 8; i++){
		if(works[i] && used[i] == -1 && grid[cur][i] == '.'){
			used[i] = cur;
			ret += amt(cur + 1);
			used[i] = -1;
		}
	}
	
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	for(int i = 0; i < 8; i++){
		cin >> grid[i];
		used[i] = -1;
	}
	
	cout << amt(0) << endl;

	return 0;
}