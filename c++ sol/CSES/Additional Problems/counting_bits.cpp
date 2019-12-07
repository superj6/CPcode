#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long n;
	cin >> n;
	
	long long ret = 0;
	for(long long i = 2; i <= 2 * n; i <<= 1){
		ret += (n / i) * i / 2 + max(n % i - i / 2 + 1, (long long)0);
	}
	
	cout << ret << endl;

	return 0;
}