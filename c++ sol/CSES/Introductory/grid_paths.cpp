#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

string s;
int used[7][7];

bool works(int x, int y){
	if(x < 0 || x >= 7 || y < 0 || y >= 7) return false;
	if(used[x][y]) return false;
	return true;
}

int amt(int x, int y, int cnt){
	
	if(works(x + 1, y) && works(x - 1, y) && !works(x, y + 1) && !works(x, y - 1)) return 0;
	if(!works(x + 1, y) && !works(x - 1, y) && works(x, y + 1) && works(x, y - 1)) return 0;
	if(!works(x + 1, y) && !works(x, y + 1) && works(x + 1, y + 1)) return 0;
	if(!works(x - 1, y) && !works(x, y + 1) && works(x - 1, y + 1)) return 0;
	if(!works(x + 1, y) && !works(x, y - 1) && works(x + 1, y - 1)) return 0;
	if(!works(x - 1, y) && !works(x, y - 1) && works(x - 1, y - 1)) return 0;
	
	if(x == 6 && y == 0){
		if(cnt == 48) return 1;
		else return 0;
	}
	
	if(cnt == 48) return 0;
	
	int ret = 0;
	
	used[x][y] = 1;
	
	if((s[cnt] == '?' || s[cnt] == 'R') && works(x, y + 1)) ret += amt(x, y + 1, cnt + 1);
	if((s[cnt] == '?' || s[cnt] == 'D') && works(x + 1, y)) ret += amt(x + 1, y, cnt + 1);
	if((s[cnt] == '?' || s[cnt] == 'L') && works(x, y - 1)) ret += amt(x, y - 1, cnt + 1);
	if((s[cnt] == '?' || s[cnt] == 'U') && works(x - 1, y)) ret += amt(x - 1, y, cnt + 1);
	
	used[x][y] = 0;
	
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s;
	memset(used, 0, sizeof(used));
	
	cout << amt(0, 0, 0) << endl;

	return 0;
}