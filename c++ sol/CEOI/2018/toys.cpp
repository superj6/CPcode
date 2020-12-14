#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
int n;
vector<int> a;
set<int> ans;
 
void recur(int x, int y, int l){
	if(y == 1){
		ans.insert(x);
		return;
	}
	for(int i : a){
		if(i * i > y) break;
		if(y % i) continue;
		if(i >= l) recur(x + i - 1, y / i, i);
		if(y / i >= l) recur(x + y / i - 1, i, y / i);
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 1; i * i <= n; i++){
		if(n % i == 0) a.push_back(i);
	}
	
	recur(0, n, 2);
	
	cout << ans.size() << endl;
	for(auto it = ans.begin(); it != ans.end(); it++){
		cout << *it;
		if(next(it) != ans.end()) cout << " ";
	}
	cout << endl;
	
	return 0;
}