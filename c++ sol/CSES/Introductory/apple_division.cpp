#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'

long long minv = 1000000000007, sum = 0;
int n;
long long a[20];

void getmin(int i, long long csum){
	if(i == n){
		minv = min(minv, abs(2 * csum - sum));
		return;
	} 
	
	getmin(i + 1, csum + a[i]);
	getmin(i + 1, csum);
	
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		sum += a[i];
	}
	
	getmin(0, 0);
	
	cout << minv << endl;

	return 0;
}