#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	long long total = 0;
	
	for(int i = 1; i < n; i++){
		if(a[i] < a[i - 1]){
			total += a[i - 1] - a[i];
			a[i] = a[i - 1];
		}
	}
	
	cout << total << endl;

	return 0;
}