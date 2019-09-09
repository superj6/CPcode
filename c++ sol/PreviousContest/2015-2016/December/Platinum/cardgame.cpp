#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

int main(){
	freopen("cardgame.in", "r", stdin);
	freopen("cardgame.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int card[n], cs[n];
	
	for(int i = 0; i < n; i++){
		cin >> card[i];
		card[i]--;
		cs[i] = card[i];
	}
	
	sort(cs, cs+n);
	
	set<int> b;
	
	for(int i = 0, j = 0; i < 2 * n; i++){
		if(cs[j] == i) j++;
		else b.insert(i);
	}
	
	int pre[n + 1], suf[n + 1];
	pre[0] = 0, suf[n] = 0;
	
	for(int i = 0; i < n; i++){
		pre[i + 1] = pre[i];
		if(b.upper_bound(card[i]) != b.end()){
			pre[i + 1]++;
			b.erase(b.upper_bound(card[i]));
		}
	}
	
	b.clear();

	for(int i = 0, j = 0; i < 2 * n; i++){
		if(cs[j] == i) j++;
		else b.insert(-i);
	}
	
	for(int i = n - 1; i >= 0; i--){
		suf[i] = suf[i + 1];
		if(b.upper_bound(-card[i]) != b.end()){
			suf[i]++;
			b.erase(b.upper_bound(-card[i]));
		}
	}
	
	int maxv = 0;
	
	for(int i = 0; i <= n; i++){
		maxv = max(maxv, pre[i] + suf[i]);
	}
	
	cout << maxv << endl;

	return 0;
}