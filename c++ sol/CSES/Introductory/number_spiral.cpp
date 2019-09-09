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
		long long y, x;
		cin >> y >> x;
		
		long long n = max(y, x) * (max(y, x) - 1) + 1;
		
		if(max(y, x) % 2 == 0){
			n += y - x;
		}else{
			n += x - y;
		}
		
		cout << n << endl;
	}

	return 0;
}