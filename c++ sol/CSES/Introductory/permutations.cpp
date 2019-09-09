#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	if(n <= 3){
		if(n == 1) cout << 1 << endl;
		else cout << "NO SOLUTION" << endl;
		return 0;
	}
	
	for(int i = n - (n % 2 == 0); i > 0; i -= 2){
		cout << i << " ";
	}
	
	for(int i = n - (n % 2 == 1); i > 2; i -= 2){
		cout << i << " ";
	}

	cout << 2 << endl;
	return 0;
}