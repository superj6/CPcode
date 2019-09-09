#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

int main(){
	freopen("dishes.in", "r", stdin);
	freopen("dishes.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int last = -1, base[n];
	vector<int> stack[n];
	
	for(int i = 0; i < n; i++) base[i] = -1;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		
		if(x < last){
			cout << i << endl;
			return 0;
		}
		
		for(int j = x; j >= 0 && base[j] == -1; j--){
			base[j] = x;
		}
		
		while(!stack[base[x]].empty() && stack[base[x]].back() < x){
			last = stack[base[x]].back();
			stack[base[x]].pop_back();
		}
		
		stack[base[x]].push_back(x);
	}
	
	cout << n << endl;

	return 0;
}