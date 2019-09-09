#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int array[n];
	memset(array, 0, sizeof(array));
	
	for(int i = 0; i < n - 1; i++){
		int a;
		cin >> a;
		a--;
		
		array[a]++;
	}
	
	for(int i = 0; i < n; i++){
		if(!array[i]){
			cout << i + 1 << endl;
			break;
		}
	}

	return 0;
}