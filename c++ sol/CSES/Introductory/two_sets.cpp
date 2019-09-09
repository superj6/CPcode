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
	
	if(n % 4 == 0){
		cout << "YES" << endl;
		
		cout << n / 2 << endl;
		cout << 1;
		for(int i = 4; i <= n; i += (i % 2 == 0 ? 1 : 3)){
			cout << " " << i;
		}
		cout << endl;
		
		cout << n / 2 << endl;
		cout << 2;
		for(int i = 3; i <= n; i += (i % 2 == 0 ? 1 : 3)){
			cout << " " << i;
		}
		cout << endl;
		
	}else if(n % 4 == 3){
		cout << "YES" << endl;
		
		cout << n / 2 + 1 << endl;
		cout << 1;
		for(int i = 2; i <= n; i += (i % 2 == 0 ? 3 : 1)){
			cout << " " << i;
		}
		cout << endl;
		
		cout << n / 2 << endl;
		cout << 3;
		for(int i = 4; i <= n; i += (i % 2 == 0 ? 3 : 1)){
			cout << " " << i;
		}
		cout << endl;
		
	}else{
		cout << "NO" << endl;
	}

	return 0;
}