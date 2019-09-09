#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	long x;
	cin >> n >> x;

	int j = 0, cnt = 0;
	long sum = 0;
	long a[n];
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		sum += a[i];
		
		while(j <= i && sum > x){
			sum -= a[j];
			j++;
		}
		
		if(sum == x) cnt++;
	}
	
	cout << cnt << endl;

	return 0;
}