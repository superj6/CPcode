#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int k = 26;
int n;
string s;
int cnt[k];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s;
	n = s.size();
	
	for(int i = 0; i < n; i++) cnt[s[i] - 'A']++;
	
	int maxv = 0;
	for(int i = 0; i < k; i++) maxv = max(maxv, cnt[i]);
	
	if(maxv > (n + 1) / 2){
		cout << -1 << endl;
		return 0;
	}
	
	for(int c = -1; n; n--){
		bool used = 0;
		for(int i = 0; i < k; i++){
			if(2 * cnt[i] - 1 == n){
				cout << (char)(i + 'A');
				cnt[i]--;
				c = i;
				used = 1;
				break;
			}
		}
		if(used) continue;
		for(int i = 0; i < k; i++){
			if(cnt[i] && i != c){
				cout << (char)(i + 'A');
				cnt[i]--;
				c = i;
				break;
			}
		}
	}
	cout << endl;

	return 0;
}