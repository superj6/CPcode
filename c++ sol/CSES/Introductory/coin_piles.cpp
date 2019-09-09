#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++){
		int a, b;
		cin >> a >> b;
		if(a > b){
			a = a + b;
			b = a - b;
			a = a - b;
		}
		
		int test = 2 * a - b;
		
		cout << (test >= 0 && test % 3 == 0 ? "YES" : "NO") << endl;
	}

	return 0;
}