/*
	For this problem, it is best to just simulate the activity with optimal moves. To move optimally, consider adding a new plate
to a stack. The plate should be put on a stack such that the bottom plate in the stack to the left it is less than it, but it is
less than the bottom plat of the stack that it is on. To do this, hold an array base showing the base stack each plate should go on,
and when you add a new plate set the base from its value to all plates currently unset less than it to have the current plate as
the base. If the new plate already has a base set, remove all plates currently of lower value as they will now be in the final stack,
and place the plate now on the top of the stack. Lastly, hold the value of the largest plate put on the stack so far, and if you ever
reach a plate less than the value of the last placed stack, you know it is impossible to add it to the final stack now, so you output
the number of stacks placed so far as your result.
*/

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
