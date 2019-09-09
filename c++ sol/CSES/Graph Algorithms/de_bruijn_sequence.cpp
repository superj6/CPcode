#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 1 << 14;
int n;
bool visited[maxn][2];
string ans;

void path(int c){
	for(int i = 0; i < 2; i++){
		if(visited[c][i]) continue;
		visited[c][i] = 1;
		path((c >> 1) | ((1 & i) << (n - 2)));
	}
	
	ans += (char)('0' + (c & 1));
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	if(n > 1){
		ans = string(n - 2, '0');
		path(0);
	}else{
		ans = "01";
	}

	cout << ans << endl;

	return 0;
}